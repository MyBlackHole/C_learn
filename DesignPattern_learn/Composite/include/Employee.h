#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

typedef struct Employee Employee;

Employee *employee_create(const char *name, const char *dept, int salary);
void employee_destroy(Employee **employee);
void employee_add(Employee *employee, Employee *subordinate);
void employee_remove(Employee *employee, Employee *subordinate);
List *employee_get_subordinates(Employee *employee);
void employee_show(Employee *employee);

#ifdef __cplusplus
}
#endif
#endif // EMPLOYEE_H_
