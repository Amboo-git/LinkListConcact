#ifndef CSV_IO_H
#define CSV_IO_H

#include "contact.h"

int exportContactsToCsv(const ContactList *list, const char *filename);
int importContactsFromCsv(ContactList *list, const char *filename);

#endif
