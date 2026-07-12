/*task2 hospital emergency dashboard paging system*/
#include <stdio.h>
#define TOTAL_PAGES 8
/* stores hospital dashboard page details */
struct Page {
int pageNumber;
char pageName[40];
};
int main(){
int pageSize;
int logicalAddress;
int pageNumber;
int offset;
struct Page pages[TOTAL_PAGES]={
{0, "triage record"},
{1,"vital signs"},
{2,"lab results"},{3,"x-ray report"},{4,"medication history"},{5,"allergy record"},{6,"doctor notes"},{7,"discharge plan"}
};
printf("Hospital Emergency Dashboard Paging System");
printf("enter page size in kb: ");
scanf("%d", &pageSize);
printf("enter logical address: ");
scanf("%d", &logicalAddress);
/*calculating page number and offset from logical address*/
pageNumber=logicalAddress/pageSize;
offset=logicalAddress % pageSize;
printf("\nlogical address: %d\n", logicalAddress);
printf("page size: %d kb\n", pageSize);
printf("page number: %d\n", pageNumber);
printf("offset: %d\n", offset);
if (pageNumber >= 0 && pageNumber < TOTAL_PAGES) {
printf("requested hospital page: %s\n",
pages[pageNumber].pageName);
} else {
printf("invalid page number.\n");
}
return 0;
}
