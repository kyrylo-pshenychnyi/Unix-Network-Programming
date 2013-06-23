#if 0

An orphan process is a computer process whose parent process has 
finished or terminated, though it remains running itself.

In a Unix-like operating system any orphaned process will be 
immediately adopted by the special init system process. This operation 
is called re-parenting and occurs automatically. Even though 
technically the process has the "init" process as its parent, it is 
still called an orphan process since the process that originally 
created it no longer exists.

A process can be orphaned unintentionally, such as when the parent 
process terminates or crashes. The process group mechanism in most 
Unix-like operation systems can be used to help protect against 
accidental orphaning, where in coordination with the user's shell will 
try to terminate all the child processes with the SIGHUP process signal, 
rather than letting them continue to run as orphans.

A process may also be intentionally orphaned so that it becomes 
detached from the user's session and left running in the background; 
usually to allow a long-running job to complete without further user 
attention, or to start an indefinitely running service. Under Unix, the 
latter kinds of processes are typically called daemon processes. The 
Unix nohup command is one means to accomplish this.

With remote invocation, a server process is also said to be orphaned 
when the client that initiated the request unexpectedly crashes after 
making the request while leaving the server process running. These 
orphaned processes waste server resources and can potentially leave a 
server starved for resources. However there are several solutions to 
the orphan process problem:

Extermination is the most commonly used technique; in this case the 
orphan is killed.
Reincarnation is a technique in which machines periodically try to 
locate the parents of any remote computations; at which point orphaned 
processes are killed.
Expiration is a technique where each process is allotted a certain 
amount of time to finish before being killed. If need be a process 
may "ask" for more time to finish before the allotted time expires.



#endif
