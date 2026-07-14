/*task2 hospital emergency dashboard paging system*/
#include <stdio.h>
#define TOTAL_PAGES 8
#define FRAMES 3
#define REQUESTS 12
/* stores hospital dashboard page details */
struct Page {
int pageNumber;
char pageName[40];
};
/*checks if requested page is already in memory or not*/
int find_page(int frames[], int page){
	for(int i=0;i<FRAMES;i++){
		if(frames[i] == page){ /*if requested page is found, it returns it position*/
			return i;
}
}
	return -1; /*else not found*/
}
/*displaying current memory frame*/
void show_frames(int frames[]){
	printf("memory frames: ");
	for(int i =0;i<FRAMES;i++){
		if(frames[i]==-1){
			printf("[empty] "); /*if frame has no page*/
}else{
			printf("[page %d] ",frames[i]);
}
}
	printf("\n");
}
/*FIFO replaces the pgae that entered memory first*/
void fifo_simulation(int requests[]){
	int frames[FRAMES]; /*stores currentpage in physixal memory*/
	int nextReplace =0; /*tells which frame should be replaced next*/
	int hits =0; /*request page in memory*/
	int pageFaults=0; /*request page not in memory*/
	for(int i=0;i<FRAMES;i++){
		frames[i]=-1;
}
	printf("FIFO Page Replacement");
	printf("Physical Memory Frames: %d\n",FRAMES);
	for(int i=0;i<REQUESTS;i++){ /*this loops processes all 12 hospital page requests*/
		int page=requests[i];
		printf("\nrequest %d: hospital page %d\n",i+1,page);
		if(find_page(frames,page)!=-1){
			hits++;
			printf("result: hit,page already in memory.\n");
}else{
			pageFaults++;
			printf("result: page fault, loading page.\n");
			frames[nextReplace]=page;
			nextReplace=(nextReplace+1)%FRAMES;
}
		show_frames(frames);
}
printf("\n fifo result\n");
printf("total requests: %d\n", REQUESTS);
printf("hits: %d\n", hits);
printf("hit ratio: %.2f\n", (float)hits / REQUESTS);
printf("miss ratio: %.2f\n", (float)pageFaults / REQUESTS);
}
/*LRU frames*/
int find_lru(int lastUsed[]){
	int minIndex =0;
	for(int i=1; i<FRAMES; i++){
		if(lastUsed[i]<lastUsed[minIndex]){
			minIndex =i;
}
}
return minIndex;
}
/*LRU replaces page that was used least recently*/
void lru_simulation(int requests[]){
	int frames[FRAMES];
	int lastUsed[FRAMES];
	int hits=0;
	int pageFaults=0;
 	for(int i=0;i<FRAMES;i++){
		frames[i]=-1;
		lastUsed[i]=-1;
}
	printf("\n LRU page replacement \n");
	printf("physical memory frames: %d\n",FRAMES);
	for(int time=0;time<REQUESTS;time++){
		int page=requests[time];
		int position=find_page(frames, page);
		printf("\n request %d: hospital page %d\n", time+1,page);
		if(position !=-1){
			hits++;
			lastUsed[position] = time;
			printf("result: hit, page already in memory.\n");
}else{
			pageFaults++;
			printf("result: page fault, loading page.\n");
			 int empty = -1;
			/*CHECK IF ANY FRAM IS EMPTY*/
			for(int i=0;i<FRAMES;i++){
				if(frames[i]==-1){
					empty=i;
					break;
}
}
			 if (empty != -1) {
                                frames[empty] = page;
                                lastUsed[empty] = time;

}else{
			int replaceIndex = find_lru(lastUsed);
			printf("replaced page %d using lru.\n",frames[replaceIndex]);
			frames[replaceIndex] = page;
                        lastUsed[replaceIndex] = time;

}
}
show_frames(frames);
}
printf("\n lru result\n");
printf("total requests: %d\n", REQUESTS);
printf("hits: %d\n", hits);
printf("page faults: %d\n", pageFaults);
printf("hit ratio: %.2f\n", (float)hits / REQUESTS);
printf("miss ratio: %.2f\n", (float)pageFaults / REQUESTS);
}


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
/*fifo page request sequence*/
int requests[REQUESTS]={
1,2,3,3,4,5,2,3,6,2,7,3
};
fifo_simulation(requests);
lru_simulation(requests);
return 0;
}
