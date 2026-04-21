#include <sys/stat.h> // Uncomment if you are on Linux/UNIX; Comment this if you are on Windows
//#include <direct.h> // Uncomment this if you are on Windows; Comment it if you are on Linux/UNIX
#include <stdio.h>
#include <string.h>
#define MAX 200

void flush(){
    FILE *file;
    FILE *comp;
    file = fopen("text-files/task.txt", "w");
    comp = fopen("text-files/completed.txt","w");
    fclose(file);
    fclose(comp);
    printf("All tasks has been deleted successfully ✔");  
}
void add_task(){
	FILE *file;
	char task[MAX];
	file = fopen("text-files/task.txt","a");
	printf("\nEnter Task (with Number): ");
	fflush(stdin);
    fgets(task,sizeof(task),stdin);
	fprintf(file,task);
	task[strlen(task)-1] = '\0';
	printf("Task Added -> %s\n", task);
	fclose(file);	
}

void show_task(){
     char content[MAX];
     char content2[MAX];
     FILE *file;
     FILE *comp;
	 printf("\n");
	 printf("[!] TASKS PENDING:\n");
	 file = fopen("text-files/task.txt","r");;
     while(fgets(content, sizeof(content),file)){
        printf("%s", content);
     }
     printf("\n");
     printf("[/] TASKS DONE:\n");
     comp = fopen("text-files/completed.txt","r");
     while(fgets(content2, sizeof(content2), comp)){
     	printf("%s", content2);
     }        
     fclose(file);
     fclose(comp);
}

void mark_task(){
    char line[512];
    int task_num;
    int current_line = 1;
    int marked = 0;
    FILE *file;
    FILE *temp;
    FILE *comp;
	printf("Enter task number to mark as completed: ");
	scanf("%d", &task_num);
	file = fopen("text-files/task.txt","r");
	temp = fopen("text-files/temp.txt", "w");
	comp = fopen("text-files/completed.txt", "a");
        if(!file || !temp){
	        printf("Error Opening a file.\n");
	}
	while(fgets(line, sizeof(line), file)) {
		if (current_line == task_num) {		      
			marked = 1;

			fprintf(comp, "%s", line);
		}else {
			fputs(line, temp);
		}
		current_line++;
	}
	fclose(file);
	fclose(temp);
	fclose(comp);
	if(!marked){
		printf("Task number %d not found.\n", task_num);
		remove("text-files/temp.txt");
	}else {
		remove("text-files/task.txt");
		rename("text-files/temp.txt","text-files/task.txt");
		printf("Task %d -> Marked as Completed [/].\n", task_num);
	}

}

int main(){
	int choice;
	do {
	printf("\n------ MENU ------\n");
	printf("<1> Add a Task\n");
	printf("<2> Show Tasks\n");
	printf("<3> Mark a Task\n");
	printf("<4> Delete all tasks\n");
	printf("<5> Exit\n");
	printf("------------------\n");
	if (scanf("%d", &choice) != 1) {
	    // handle non-integer input
	    while (getchar() != '\n');
	    choice = 0;
	    continue;
	}
	while (getchar() != '\n');	
    switch(choice) {
    	case 1: add_task(); break;
    	case 2: show_task(); break;
    	case 3: mark_task(); break;
    	case 4: flush(); break;
    	case 5: printf("Have a Good Day!\n"); break;
    	default: printf("Invalid Choice\n");
    }
  }while(choice  != 5 );
  return 0;
}
