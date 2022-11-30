#pragma once

struct Il2CppObject;
struct Il2CppDelegate;
struct Il2CppAsyncResult;

namespace il2cpp
{
namespace vm
{

class ThreadPool
{
public:

	struct Configuration
	{
		int minThreads;
		int maxThreads;
		int minAsyncIOThreads;
		int maxAsyncIOThreads;

		// These are read-only.
		int availableThreads;
		int availableAsyncIOThreads;
	};

	static void Initialize ();
	static void Shutdown ();

	/// On a thread, call the given delegate with 'params' as arguments. Upon completion,
	/// call 'asyncCallback'.
	static Il2CppAsyncResult* Queue (Il2CppDelegate* delegate, void** params, Il2CppDelegate* asyncCallback, Il2CppObject* state);

	/// Wait for the execution of the given asynchronous call to have completed and return
	/// the value returned by the delegate wrapped in the call (or null if the delegate has
	/// a void return type).
	/// NOTE: Any AsyncResult can only be waited on once! Repeated or concurrent calls to Wait() on the same AsyncResult
	///       will throw InvalidOperationExceptions.
	static Il2CppObject* Wait (Il2CppAsyncResult* asyncResult, void** outArgs);

	static Configuration GetConfiguration ();
	static void SetConfiguration (const Configuration& configuration);
};

} /* namespace vm */
} /* namespace il2cpp */
