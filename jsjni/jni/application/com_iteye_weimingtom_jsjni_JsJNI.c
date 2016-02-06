#include "com_iteye_weimingtom_jsjni_JsJNI.h"
#include <stdlib.h>
#include <stdio.h>

#if defined ANDROID
#include <jni.h>
#include <stdlib.h>
#include <android/log.h>
#endif

// This is an example for SpiderMonkey 31.
// For SpiderMonkey 24 or 38, see each comment.

// following code might be needed in some case
// #define __STDC_LIMIT_MACROS
// #include <stdint.h>
#include <jsapi.h>

extern int main_();

JNIEXPORT jint Java_com_iteye_weimingtom_jsjni_JsJNI_exec
  (JNIEnv *env, jobject obj, jstring filename)
{
    char bufFilename[256] = {0};
    const char *strFilename;
	int ret = 0;

    strFilename = (*env)->GetStringUTFChars(env, filename, NULL);
    if (strFilename == NULL) {
        return -1; /* OutOfMemoryError already thrown */
    }
    //printf("%s", strFilename);
    snprintf(bufFilename, sizeof(bufFilename) - 1, "%s", strFilename);
    (*env)->ReleaseStringUTFChars(env, filename, strFilename);

    main_();

	return ret;
}

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

// The error reporter callback.
void
reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    fprintf(stderr, "%s:%u: %s\n",
            report->filename ? report->filename : "<no filename>",
            (unsigned int) report->lineno,
            message);
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
			"[%s:%d %s]%s:%u: %s", __FILE__, __LINE__, __FUNCTION__,
			report->filename ? report->filename : "<no filename>",
			(unsigned int) report->lineno,
			message);
#endif
}


//http://d.hatena.ne.jp/ytakano/20100519/1274230565
int main_()
{
        // JS variables.
        JSRuntime *rt;
        JSContext *cx;
        JSObject  *global;

        /*
         * Create a JS runtime.
         *
         * JSRuntime * JS_NewRuntime(uint32 maxbytes);
         *   maxbytes: Maximum number of allocated bytes after which garbage
         *             collection is run.
         */
        rt = JS_NewRuntime(8L * 1024L * 1024L);
        if (rt == NULL) {
            fprintf(stderr, "failed to create a JS runtime\n");
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
			"[%s:%d %s]%s", __FILE__, __LINE__, __FUNCTION__,
			"failed to create a JS runtime");
#endif
                return 1;
        }

        /*
         * Create a context.
         *
         * JSContext * JS_NewContext(JSRuntime *rt, size_t stackchunksize);
         *   rt: Parent runtime for the new context. JavaScript objects,
         *       functions, strings, and numbers may be shared among the
         *       contexts in a JSRuntime, but they cannot be shared across
         *       JSRuntimes.
         *   stackchunksize: The size, in bytes, of each "stack chunk". This is
         *                   a memory management tuning parameter which most
         *                   users should not adjust. 8192 is a good default
         *                    value.
         */
        cx = JS_NewContext(rt, 8192);
        if (cx == NULL) {
        	fprintf(stderr, "failed to create a context\n");
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
			"[%s:%d %s]%s", __FILE__, __LINE__, __FUNCTION__,
			"failed to create a context");
#endif
            return 1;
        }
        JS_SetOptions(cx, JSOPTION_VAROBJFIX);
        JS_SetVersion(cx, JSVERSION_DEFAULT/*JSVERSION_LATEST*/);
        JS_SetErrorReporter(cx, reportError);

        /*
         * Create the global object.
         *
         * JSObject * JS_NewObject(JSContext *cx, JSClass *clasp,
         *                         JSObject *proto, JSObject *parent);
         *   cx: The context in which to create the new object. Requires
         *       request.
         *   clasp: Pointer to the class to use for the new object. If this is
         *          NULL, an ordinary JavaScript Object is created.
         *   proto: Pointer to the prototype object to use for the new object.
         *          The new object will inherit all of the prototype object's
         *          properties and methods, and the new object's __proto__
         *          property will be a reference to the prototype object.
         *   parent: Pointer to the parent of the new object. The new object's
         *           __parent__  property will be a reference to this object. If
         *           parent is NULL, a default parent object is used.
         */
        global = JS_NewObject(cx, &global_class, NULL, NULL);
        if (global == NULL) {
                fprintf(stderr, "failed to create the global object\n");
    #ifdef ANDROID
    		__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
    			"[%s:%d %s]%s", __FILE__, __LINE__, __FUNCTION__,
    			"failed to create the global object");
    #endif
                return 1;
        }

        /* Populate the global object with the standard globals,
           like Object and Array. */
        if (! JS_InitStandardClasses(cx, global)) {
                fprintf(stderr, "failed to populate the global object.\n");
    #ifdef ANDROID
    		__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
    			"[%s:%d %s]%s", __FILE__, __LINE__, __FUNCTION__,
    			"failed to populate the global object.");
    #endif
                return 1;
        }

        {
                jsval rval;
                JSBool ok;
                char *source = "x=1; y=2; x+y";

				 ok = JS_EvaluateScript(cx, global, source, strlen(source),
						 __FILE__, __LINE__, &rval);
				 if (ok)
				 {
						 jsdouble d;
						 ok = JS_ValueToNumber(cx, rval, &d);
						fprintf(stderr, "Return: %f\n", d);
			#ifdef ANDROID
					__android_log_print(ANDROID_LOG_ERROR, "jsjni.c",
						"[%s:%d %s]%s %f", __FILE__, __LINE__, __FUNCTION__,
						"Return: ", d);
			#endif
				 }
        }


        JS_DestroyContext(cx);
        JS_DestroyRuntime(rt);
        JS_ShutDown();
        return 0;
}

