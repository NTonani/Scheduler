#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"
#include "node.h"
#include <sys/time.h>

void setTime(Node **head);
int runPriority(Node **head);
void addLast(Node **head, PCB* add);
void clearTempList(Node **head);
void clearList(Node **head);

static int curT;

int main(){
	struct timeval tv1,tv2;
	double diff = 0.0;
	int id,priority,size;
	int algChoice = -1;
	
	long arrival,burst;
	Node * head = NULL;
	Node * head1 = NULL;
	FILE *file = fopen("setup.txt","r");
	while(fscanf(file,"%d %d %d %d",&id,&arrival,&burst,&priority)==4){
		PCB *temp = (PCB*)malloc(sizeof(PCB));
		temp->processID = id;
		temp->arrivalTimeStamp = arrival;
		temp->totalBurstTime = burst;
		temp->processPriority = priority;
		temp->remainingBurstTime = burst;
		temp->executionStartTime =0;
		temp->executionEndTime = 0;
		addLast(&head,temp);
		size++;
	}
	fclose(file);
	do{
		printf("Please choose the algorithm you'd like the scheduler to use:\n1.)Priority-based Non-Preemptive Scheduling\n2.)Shortest-Job-First Non-Preemptive Scheduling\n");
		scanf("%d",&algChoice);
		
		if(algChoice!=1 && algChoice!=2){
			printf("Invalid algorithm chosen");
		}
	}while(algChoice!=1 && algChoice!=2);
	curT = ((int)((PCB*)head->data)->arrivalTimeStamp);
	setTime(&head);
	
	gettimeofday(&tv1, 0);
	
	if(algChoice==1){
		while(runPriority(&head)==1);
	}else if(algChoice==2){
		while(runSJF(&head)==1);
	}else{
		printf("Incorrect\n");
	}
	

	gettimeofday(&tv2, 0);
	double tot_time = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec);
	printf("Finished with time %f\n",tot_time);
	
	clearList(&head);
}

void setTime(Node **head){
	Node *temp = *head;
	while(temp!=NULL){
		if(((int)((PCB*)temp->data)->arrivalTimeStamp)<curT){
			curT = ((int)((PCB*)temp->data)->arrivalTimeStamp);
		}
		temp = temp->next;
	}
}

int runSJF(Node **head){
	Node *temp = *head;
	Node *thead = NULL;
	int num = 0;
	int id = -1;
	int check = 0;
	while(temp!=NULL){
		if(((int)((PCB*)temp->data)->arrivalTimeStamp) <= curT){
			if(((PCB*)temp->data)->remainingBurstTime >0){
				addLast(&thead,(PCB*)temp->data);
				num++;
			}
		}
		check++;
		temp = temp->next;
	}
	if(thead==NULL){
		return 0;
	}
	int sj = (int)((PCB*)(thead->data))->totalBurstTime;
	temp = thead;
	while(temp!=NULL){
		if(((int)((PCB*)(temp->data))->totalBurstTime)<sj){
			sj = (int)((PCB*)(temp->data))->totalBurstTime;
		}
		temp = temp->next;
	}
	temp = thead;
	while(((int)((PCB*)(temp->data))->totalBurstTime)!=sj){
		temp = temp->next;
	}
	printf("Executing process %d\n",((PCB*)temp->data)->processID);
	curT+=((PCB*)temp->data)->remainingBurstTime;
	((PCB*)temp->data)->remainingBurstTime = 0;
	clearTempList(&thead);

	return 1;

}

int runPriority(Node **head){
	Node *temp = *head;
	Node *thead = NULL;
	int num = 0;
	int id = -1;
	while(temp!=NULL){
		if(((int)((PCB*)temp->data)->arrivalTimeStamp) <= curT){
			if(((PCB*)temp->data)->remainingBurstTime >0){
				addLast(&thead,(PCB*)temp->data);
				num++;
			}
			
		}
		temp = temp->next;
	}
	if(thead==NULL){
		return 0;
	}
	temp = thead;
	int mp = ((PCB*)(thead->data))->processPriority;
	while(temp!=NULL){
		if(((PCB*)(temp->data))->processPriority>mp){
			mp = ((PCB*)(temp->data))->processPriority;
		}
		temp = temp->next;
	}
	temp = thead;
	while(((PCB*)temp->data)->processPriority!=mp){
		temp = temp->next;
	}
	printf("Executing process %d\n",((PCB*)temp->data)->processID);
	curT+=((PCB*)temp->data)->remainingBurstTime;
	((PCB*)temp->data)->remainingBurstTime = 0;
	clearTempList(&thead);

	return 1;

}

void addLast(Node **head, PCB* add)
{
	Node *temp; 
	temp = *head;
	Node *var = (Node *)malloc(sizeof(Node));
	var->data = add;
	if(*head==NULL)
        {
            *head=var;
            (*head)->next=NULL;
        }
        else
        {
            while(temp->next!=NULL)
            {     
                 temp=temp->next;
            }
            var->next=NULL;
            temp->next=var;
        }
}
void clearTempList(Node **head){
	Node *prev,*cur;
	cur = *head;
	while(cur!=NULL){
		prev = cur;
		cur = cur->next;
		free(prev);
		prev=NULL;
	}
	*head = NULL;
	
}
void clearList(Node **head){
	Node *prev,*cur;
	cur = *head;
	while(cur!=NULL){
		prev = cur;
		cur = cur->next;
		free((PCB*)prev->data);
		prev->data=NULL;
		free(prev);
		prev=NULL;
	}
	*head = NULL;
	
}
