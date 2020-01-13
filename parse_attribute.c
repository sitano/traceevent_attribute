#include "traceevent/event-parse.h"
#include "traceevent/event-parse-local.h"

#include <stdio.h>

// export TOOLS=~/Projects/linux-5.4.2-arch1/tools && gcc -g -I $TOOLS/lib -I $TOOLS/include parse_attribute.c $TOOLS/lib/traceevent/event-parse.c $TOOLS/lib/traceevent/trace-seq.c $TOOLS/lib/traceevent/parse-utils.c $TOOLS/lib/traceevent/event-parse-api.c
// Attributes in C: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2137.pdf
//
// Error: expected type 4 but read 5
//
// Does traceevent support GCC type attributes?
//
// Patch:
// 				/* ignore C attributes: __attribute__((expr)) */
// 				if (strcmp(token, "__attribute__") == 0) {
// 					free(token);
// 					for (int i = 0; i < 2; i ++) {
// 						if (read_expected_item(TEP_EVENT_DELIM, "(") < 0) {
// 							goto fail_expect;
// 						}
// 					}
// 					for (int brackets = 2; brackets > 0;) {
// 						if (read_token(&token) == TEP_EVENT_NONE) {
// 							do_warning_event(event, "%s: __attribute__ not full", __func__);
// 							goto fail_expect;
// 						}
// 						if (strcmp(token, "(") == 0) brackets++;
// 						else if (strcmp(token, ")") == 0) brackets--;
// 						free(token);
// 					}
// 					continue;
// 				}
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
    "	field:struct rusage __attribute__ ( \n( user,blah, \nformat( \"ups())\\\", 2,3 ))()\", 1, 2), __q)) * field1;	offset:40;	size:8;	signed:0;\n"
    "\n"
    "print fmt: \"\"";
  unsigned long size = strlen(buf);
  const char *sys = "ftrace";
  enum tep_errno err;

  printf("parsing:\n%s\n", buf);
  err = tep_parse_format(&tep, &ev, buf, size, sys);
  if (err) {
    printf("err = %d", err);
    return err;
  }

  printf("Parsed:\n");
  struct tep_format_field *field = ev->format.fields;
  while (field) {
    printf("name:%s type:%s alias:%s offset:%d size:%d\n",
      field->name, field->type, field->alias,
      field->offset, field->size);
    field = field->next;
  }

  return 0;
}

// void f(int __attribute__ (
//       ( user,user, user(1,2,3, "a"), blah(
//           "blah()()(\"())") ) ) a) {
//   printf("%d", a);
// }
