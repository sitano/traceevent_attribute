# traceevent attribute

Test for linux kernel traceevent library __attribute__ support
at least of version 5.4.

# Quick start

```
$ sudo cat /sys/kernel/debug/tracing/events/syscalls/sys_enter_io_submit/format

name: sys_enter_io_submit
ID: 897
format:
	field:unsigned short common_type;	offset:0;	size:2;	signed:0;
	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;
	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;
	field:int common_pid;	offset:4;	size:4;	signed:1;

	field:int __syscall_nr;	offset:8;	size:4;	signed:1;
	field:aio_context_t ctx_id;	offset:16;	size:8;	signed:0;
	field:long nr;	offset:24;	size:8;	signed:0;
	field:struct iocb __attribute__((user)) * __attribute__((user)) * iocbpp;	offset:32;	size:8;	signed:0;

print fmt: "ctx_id: 0x%08lx, nr: 0x%08lx, iocbpp: 0x%08lx", ((unsigned long)(REC->ctx_id)), ((unsigned long)(REC->nr)), ((unsigned long)(REC->iocbpp))

$ sudo perf record -e syscalls:sys_enter_io_submit -aR

libtraceevent: No such file or directory
  Error: expected type 4 but read 5
^C[ perf record: Woken up 1 times to write data ]

```

libtraceevent must not report error for parsing tracepoint format.
It breaks at `__attribute__((user))` that is GCC extension.

This attribute comes from <https://elixir.bootlin.com/linux/latest/source/include/linux/compiler_types.h#L28>:

```
# ifdef STRUCTLEAK_PLUGIN
#  define __user __attribute__((user))
# else
```

the kernel built with STRUCTLEAK_PLUGIN.

# Compile

 gcc -I ~/Projects/linux-5.4.2-arch1/tools/lib -I ~/Projects/linux-5.4.2-arch1/tools/include parse_attribute.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/event-parse.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/trace-seq.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/parse-utils.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/event-parse-api.c

# Doc

Attributes in C: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2137.pdf

# Error

```
Error: expected type 4 but read 5
```
