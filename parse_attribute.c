#include "traceevent/event-parse.h"
#include "traceevent/event-parse-local.h"

#include <stdio.h>

// gcc -I ~/Projects/linux-5.4.2-arch1/tools/lib -I ~/Projects/linux-5.4.2-arch1/tools/include parse_attribute.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/event-parse.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/trace-seq.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/parse-utils.c ~/Projects/linux-5.4.2-arch1/tools/lib/traceevent/event-parse-api.c
// Attributes in C: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2137.pdf
//
// Error: expected type 4 but read 5
//
// Does traceevent support GCC type attributes?
int main() {
  struct tep_handle tep = {.handlers=NULL};
  struct tep_event *ev;
  char *buf =
    "name: sys_enter_wait4\n"
    "ID: 140\n"
    "format:\n"
    "	field:unsigned short common_type;	offset:0;	size:2;	signed:0;\n"
    "	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;\n"
    "	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;\n"
    "	field:int common_pid;	offset:4;	size:4;	signed:1;\n"
    "\n"
    "	field:struct rusage __attribute__ ( ( user,blah, ah( \"ups())\\\" ))()\", 1, 2), __q)) * ru;	offset:40;	size:8;	signed:0;\n"
    "\n"
    "print fmt: \"\"";
  unsigned long size = strlen(buf);
  const char *sys = "ftrace";
  enum tep_errno err;

  printf("parsing:\n%s\n", buf);
  err = tep_parse_format(&tep, &ev, buf, size, sys);
  if (err) {
    printf("err = %d", err);
  }

  return err;
}

void f(int __attribute__ (
      ( user,user, user(1,2,3, "a"), blah(
          "blah()()(\"())") ) ) a) {
  printf("%d", a);
}
