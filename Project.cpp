#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<time.h>

struct Friend{
    char friendname[255];
    Friend *next, *prev;
};

struct Inbox{
    char sender[255];
    Inbox *next, *prev;
};

struct Request{
    char sendto[255];
    Request *next, *prev;
};

struct Candidate {
    char candidatename[255];
    Candidate *next, *prev;
};

struct User {
    char username[255];
    char password[255];
    Candidate *headcandidate, *tailcandidate;
    Friend *headfriend, *tailfriend;
    Inbox *headinbox, *tailinbox;
    Request *headrequest, *tailrequest;
    User *next, *prev;
} *headuser, *tailuser, *auth, *dest;

User *createUser(const char *name, const char *password) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->username, name);
    strcpy(newUser->password, password);
    newUser->next = newUser->prev = NULL;
    return newUser;
}

Friend *createFriend(const char *name){
    Friend *newFriend = (Friend *)malloc(sizeof(Friend));
    strcpy(newFriend->friendname,name);
    return newFriend;
}

Candidate *createCandidate(const char *name){
    Candidate *newCandidate = (Candidate *)malloc(sizeof(Candidate));
    strcpy(newCandidate->candidatename,name);
    return newCandidate;
}

Request *createRequest(const char *name){
    Request *newRequest = (Request *)malloc(sizeof(Request));
    strcpy(newRequest->sendto,name);
    return newRequest;
}

Inbox *createInbox(const char *name){
    Inbox *newInbox = (Inbox *)malloc(sizeof(Inbox));
    strcpy(newInbox->sender,name);
    return newInbox;
}

void pushUser(const char *name, const char *password) {
    User *temp = createUser(name, password);

    if(!headuser) {
        headuser = tailuser = temp;
    }
    else {
        tailuser->next = temp;
        temp->prev = tailuser;
        tailuser = temp;
    }
}

void pushCandidate(const char *name, User *user) {
    Candidate *temp = createCandidate(name);

    if(!user->headcandidate) {
        user->headcandidate = user->tailcandidate = temp;
    }
    else {
        user->tailcandidate->next = temp;
        temp->prev = user->tailcandidate;
        user->tailcandidate = temp;
    }
}

void pushFriendDest(const char *name) {
    Friend *temp = createFriend(name);

    if(!dest->headfriend) {
       dest->headfriend = dest->tailfriend = temp;
    }
    else {
        dest->tailfriend->next = temp;
        temp->prev = dest->tailfriend;
        dest->tailfriend = temp;
    }
}

void pushFriendAuth(const char *name) {
    Friend *temp = createFriend(name);

    if(!auth->headfriend) {
       auth->headfriend = auth->tailfriend = temp;
    }
    else {
        auth->tailfriend->next = temp;
        temp->prev = auth->tailfriend;
        auth->tailfriend = temp;
    }
}

void pushRequest(const char *name) {
    Request *temp = createRequest(name);

    if(!auth->headrequest) {
       auth->headrequest = auth->tailrequest = temp;
    }
    else {
        auth->tailrequest->next = temp;
        temp->prev = auth->tailrequest;
        auth->tailrequest = temp;
    }
}
void popCandidate(const char* name, User* user){
	if (!user->headcandidate)
  { 
    return;
  }
  else if (strcmp(user->headcandidate->candidatename,name)==0)
  {
    if(!user->headcandidate){
        return;
    }else if(user->headcandidate==user->tailcandidate){
        free(user->headcandidate);
        user->headcandidate = NULL;
    }else{
        Candidate *temp = user->headcandidate->next;
        user->headcandidate->next = temp->prev = NULL;
        free(user->headcandidate);
        user->headcandidate =  temp;
    }
  }
  else if (strcmp(user->tailcandidate->candidatename , name)==0)
  {
    if (!user->headcandidate)
    {
        return;
     }
     else if (user->headcandidate == user->tailcandidate)
    {
     free(user->headcandidate);
     user->headcandidate = user->tailcandidate = NULL;
    }
    else
     {                                    
        Candidate *newTail = user->tailcandidate->prev;        
        user->tailcandidate->prev = newTail->next = NULL; 
     free(user->tailcandidate);                        
     user->tailcandidate = newTail;                
     }
  }
  else
  {                   
    Candidate *curr = user->headcandidate; 
    while (curr && strcmp(curr->candidatename ,name)!=0)
    {
      curr = curr->next; 
    }

    curr->prev->next = curr->next; 
    curr->next->prev = curr->prev; 

    curr->prev = curr->next = NULL; 
    free(curr);                     
    curr = NULL;                    
  }
}
void pushInbox(const char *name) {
    Inbox *temp = createInbox(name);

    if(!dest->headinbox) {
       dest->headinbox = dest->tailinbox = temp;
    }
    else {
        dest->tailinbox->next = temp;
        temp->prev = dest->tailinbox;
        dest->tailinbox = temp;
    }
}

void popRequest(const char *name){
 
    if (!dest->headrequest){ 
        return;
    }
    else if(dest->headrequest==dest->tailrequest){
  	    free(dest->headrequest);
        dest->headrequest = NULL;
    }
    else if (strcmp(dest->headrequest->sendto,name)==0){
        Request *temp = dest->headrequest->next;
        dest->headrequest->next = temp->prev = NULL;
        free(dest->headrequest);
        dest->headrequest =  temp;
    }
    else if (strcmp(dest->tailrequest->sendto,name)==0){                             
        Request *newTail = dest->tailrequest->prev;        
        dest->tailrequest->prev = newTail->next = NULL; 
        free(dest->tailrequest);                        
        dest->tailrequest = newTail;                
    }
    else{                   
        Request *curr = dest->headrequest; 
        while (curr && strcmp(curr->sendto ,name)!=0){
            curr = curr->next; 
        }

        curr->prev->next = curr->next; 
        curr->next->prev = curr->prev; 

        curr->prev = curr->next = NULL; 
        free(curr);                     
        curr = NULL;                    
    }
}

void popInbox(const char *name){
  	if (!auth->headinbox){ 
    	return;
  	}
  	else if(auth->headinbox == auth->tailinbox){
        free(auth->headinbox);
        auth->headinbox = NULL;
	}
  	else if (strcmp(auth->headinbox->sender, name) == 0){
        Inbox *temp = auth->headinbox->next;
        auth->headinbox->next = temp->prev = NULL;
        free(auth->headinbox);
        auth->headinbox =  temp;
  	}
  	else if (strcmp(auth->tailinbox->sender, name) == 0){                                 
        Inbox *newTail = auth->tailinbox->prev;        
        auth->tailinbox->prev = newTail->next = NULL; 
    	free(auth->tailinbox);                        
    	auth->tailinbox = newTail;                   
  	}
  	else{                   
	    Inbox *curr = auth->headinbox; 
	    
	    while (curr && strcmp(curr->sender,name)!=0){
	      curr = curr->next; 
	    }
	
	    curr->prev->next = curr->next; 
	    curr->next->prev = curr->prev; 
	
	    curr->prev = curr->next = NULL; 
	    free(curr);                     
	    curr = NULL;                    
  	}
}

void popCandidate();
void popFriend();
void Dashboard();
void addFriend();
void removeFriend();
void viewInbox();
void viewSentRequest();
void notes();
void Register();
void Login();

void MainMenu(){
    system("cls");
    printf("Oo================================================oO\n");
    printf("                   STUDY NETWORK                    \n");
    printf("Oo================================================oO\n");
    printf("[All User]\n");
    printf("No.        Username\n");
    User *cur = headuser;
    int cnt = 1;
    while(cur){
        printf("%d.         %s\n",cnt,cur->username);
        cnt++;
        cur = cur->next;
    }
    printf("....................................................\n");
    printf("[1] Register\n");
    printf("[2] Login\n");
    printf("[3] Exit\n");
    printf("....................................................\n");
    printf("Press 0 and enter to abort an operation\n");
    printf("....................................................\n");
    int number;
	scanf("%d",&number);
	switch(number){
		case 1:
			Register();
			break;
		case 2:
			Login();
			break;
        default:
            printf("You've exited the application\n");
    }
}

void Register(){
    system("cls");
    char name[255];
    int tanda;
    int len;
    do{
     	tanda = 0;
        printf("Please type in your username[Lowercase][1..24] : ");
        scanf("%s",name);
        len = strlen(name);
         if(len>24){
             tanda = 1;
         }
         for(int i=0;i<len;i++){
         	if(!(name[i]>='a' && name[i]<='z')){
         		tanda = 1;
         		break;
			 }
		 }
     }while(tanda == 1);
    char pass[255];
    do{
     	tanda = 0;
        printf("Please type in your password[Lowercase][1..24] : ");
        scanf("%s",&pass);
        len = strlen(pass);
         if(len>24){
             tanda = 1;
         }
         for(int i=0;i<len;i++){
         	if(!(pass[i]>='a' && pass[i]<='z')){
         		tanda = 1;
         		break;
			 }
		 }
     }while(tanda == 1);
    User *cur = headuser;
    bool found = false;
    while(cur){
        if(strcmp(cur->username,name) == 0){
            found = true;
            break;
        }
        cur = cur->next;
    }
    if(found){
        printf("--- This Username has been taken ---\n");
        printf("Press enter to continue");
        getchar();getchar();
        Register();
    }else{
        pushUser(name,pass);
        User *temp;
        temp = headuser;
        while(temp){
           if(strcmp(temp->username,name)==0){
               break;
           }
           temp = temp->next;
        }
        User *cr = headuser;
        while(cr){
            if(strcmp(cr->username,name)!=0){
                pushCandidate(cr->username,temp);
                pushCandidate(temp->username,cr);
            }
            cr = cr->next;
        }
        
        printf("--- Registration Succesfull ---\n");
        printf("Press enter to continue");
        getchar();getchar();
        MainMenu();
    }
}

void Login(){
    system("cls");
    printf("Username : ");
    char name[255];
    scanf("%s",&name);
    printf("Password : ");
    char pass[255];
    scanf("%s",&pass);
    User *cur = headuser;
    bool cek = false;
    while(cur){
        if(strcmp(cur->username,name)==0  && strcmp(cur->password,pass)==0){
            auth = cur;
            cek = true;
            break;
        }
        cur = cur->next;
    }
    if(cek){
        printf("--- Login Succesfull ---\n");
         printf("Press enter to continue!\n");
         getchar(); getchar();
         Dashboard();

    }else{
        printf("--- Username/Password Inccorect ---\n");
         printf("Press enter to continue!\n");
        getchar(); getchar();
        Login();
    }
}

void Dashboard(){
    clock_t begin = clock();


    system("cls");
    printf("Oo================================================oO\n");
    printf("Welcome, %s !\n",auth->username);
    printf("Oo================================================oO\n");
    printf("Logged in: %s %s\n",__DATE__,__TIME__);
    printf("----------------------------------------------------\n");
    printf("\n\n");
    printf("[All Friends of %s]\n",auth->username);
    Friend *cur = auth->headfriend;
    printf("No.        Username\n");
    int cnt = 1;
    if(cur){
        while(cur){
                printf("%d.         %s\n",cnt,cur->friendname);
                cnt++;
            cur = cur->next;
        }
    }
    printf("....................................................\n");
    printf("                    >>Menu<<                        \n");
    printf("....................................................\n");
    printf("[1] Add Friend\n");
    printf("[2] Remove Friend\n");
    printf("[3] View Inbox\n");
    printf("[4] View Sent Request\n");
    printf("[5] Add, Edit, Annouce, Delete Note\n");
    printf("[6] Log out\n");
    printf("....................................................\n");
    int number;
	scanf("%d",&number);
    switch(number){
		case 1:
			addFriend();
			break;
		case 2:
			removeFriend();
			break;
        case 3:
            viewInbox();
        case 4:
            viewSentRequest();
        case 5:
            notes();
        default:
            auth = NULL;
            clock_t end = clock();
            int time_spent = (int)(end - begin) / CLOCKS_PER_SEC;     
            printf("--- You've logged out ---\n");
            printf("You have used this application for %02d(h):%02d(m):%02d(s)\n",time_spent/3600,(time_spent%3600)/60,(time_spent%3600)%60);
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); MainMenu();
    }
  
}
void addFriend(){
    system("cls");
    printf("[All User]\n");
    printf("No.        Username\n");
    Candidate *cur = auth->headcandidate;
    int cnt = 1;
    while(cur){
        if(strcmp(auth->username,cur->candidatename)!=0){
            printf("%d.         %s\n",cnt,cur->candidatename);
            cnt++;    
        }
         cur = cur->next;
    }
    printf("\n\n");
    printf("Which user do you want to add ?\n");
    char name[255];
    scanf("%s", &name);
    User *curr = headuser;
    bool found = false;
    while(curr){
        if(strcmp(name,curr->username)==0 && strcmp(name,auth->username)!=0){
            dest = curr;
            found = true;
            break;
        }
        curr = curr->next;
    }
    if(found){
        pushRequest(name);
        pushInbox(auth->username);
        popCandidate(name,auth);
        printf("--Your request has been sent to %s--\n",name);
        printf("Press Enter to Continue!\n");
        getchar(); getchar(); Dashboard();
    }else{
            printf("No user found!\n");
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); Dashboard();
    }
    

}

void popFriend(const char* name, User* user){
	if (!user->headfriend)
  { 
    return;
  }
  else if (strcmp(user->headfriend->friendname,name)==0)
  {
    if(!user->headfriend){
        return;
    }else if(user->headfriend==user->tailfriend){
        free(user->headfriend);
        user->headfriend = NULL;
    }else{
        Friend *temp = user->headfriend->next;
        user->headfriend->next = temp->prev = NULL;
        free(user->headfriend);
        user->headfriend =  temp;
    }
  }
  else if (strcmp(user->tailfriend->friendname , name)==0)
  {
    if (!user->headfriend)
    {
        return;
     }
     else if (user->headfriend == user->tailfriend)
    {
     free(user->headfriend);
     user->headfriend = user->tailfriend = NULL;
    }
    else
     {                                    
        Friend *newTail = user->tailfriend->prev;        
        user->tailfriend->prev = newTail->next = NULL; 
     free(user->tailfriend);                        
     user->tailfriend = newTail;                
     }
  }
  else
  {                   
    Friend *curr = user->headfriend; 
    while (curr && strcmp(curr->friendname ,name)!=0)
    {
      curr = curr->next; 
    }

    curr->prev->next = curr->next; 
    curr->next->prev = curr->prev; 

    curr->prev = curr->next = NULL; 
    free(curr);                     
    curr = NULL;                    
  }
}

void removeFriend(){
	system ("cls");
    printf("[All Friends of %s]\n",auth->username);
	printf("No.        Username\n");
	Friend *cur;
	cur = auth->headfriend;
	int cnt = 1;
	if(cur){
		while(cur){
			printf("%d.         %s\n",cnt,cur->friendname);
			cur = cur->next;
            cnt++;
		}
		printf("Which user do you want to remove?\n");
		char username[255];
		scanf("%s",username);
		cur = auth->headfriend;
		User *curr = headuser;
		while(curr){
			if(strcmp(curr->username, username) == 0){
				dest = curr;
				break;
			}
			curr = curr->next;
		}
		while(cur){
			if(strcmp(cur->friendname,username)==0){
				popFriend(username, auth);
                pushCandidate(username,auth);
				popFriend(auth->username, dest);
                pushCandidate(auth->username,dest);
				break;
			}
			cur = cur->next;
		}
		printf("-- You are no longer friends with %s -- \n",username);
		printf("Press enter to continue!");
		getchar(); getchar(); Dashboard();
	}
	else{
		printf("-- You don't have any friends --\n");
        printf("Press Enter to Continue!\n");
        getchar(); getchar(); Dashboard();
	}
}

void viewInbox(){
    system("cls");
    printf("[All Friend Requests of %s]\n",auth->username);
    printf("No.        Username\n");
    Inbox *cur = auth->headinbox;
    int cnt = 1;
    if(cur){
        while(cur){
             printf("%d.         %s\n",cnt,cur->sender);
             cnt++;
             cur = cur->next;
        }
        printf("Which user do you want to be accepted?\n");
        char name[255];
        scanf("%s",&name);
        User *tmp = headuser;
        bool find =false;
        while(tmp){
            if(strcmp(tmp->username,name)==0  && strcmp(tmp->username,auth->username)!=0){
                dest = tmp;
                find = true;
                break;
            }
            tmp = tmp->next;
        }
        if(find){
            pushFriendAuth(name);
            pushFriendDest(auth->username);
            popRequest(auth->username);
            popInbox(name);
            popCandidate(name, auth);
            printf("-- You accepted the requests from %s --\n",name);
            printf("Press enter to continue!\n");
            getchar(); getchar(); Dashboard();
        }else{
            printf("-- User Not Found! --\n");
            printf("Press enter to continue!\n");
            getchar(); getchar(); Dashboard();
        }

    }else{
        printf("-- You don't have any friend requests --\n");
        printf("Press Enter to Continue!\n");
        getchar(); getchar(); Dashboard();
    }
    
    }
    
void viewSentRequest(){
    system("cls");
    printf("[All Sent Requests of %s]\n",auth->username);
    printf("No.        Username\n");
    Request *cur = auth->headrequest;
    int cnt = 1;
    if(cur){
        while(cur){
             printf("%d.         %s\n",cnt,cur->sendto);
             cnt++;
             cur = cur->next;
        }
        printf("\n");
        printf("Press Enter to continue\n");
        getchar(); getchar(); Dashboard();
    }else{
        printf("\n");
        printf("You haven't send any request\n");
        printf("Press Enter to continue\n");
        getchar(); getchar(); Dashboard();
    }
}
void notes(){
    return;
}

int main(){
    MainMenu();
}