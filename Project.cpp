#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
struct Friend{
    char status[255];
    char friendname[255];
    Friend *next, *prev;

};
struct User {
    char username[255];
    char password[255];
    Friend *headfriend, *tailfriend;
    User *next, *prev;
} *headuser, *tailuser, *auth;

User *createUser(const char *name, const char *password) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->username, name);
    strcpy(newUser->password, password);
    newUser->next = newUser->prev = NULL;
    return newUser;
}

Friend *createFriend(const char *name, const char *status){
    Friend *newFriend = (Friend *)malloc(sizeof(Friend));
    strcpy(newFriend->friendname,name);
    strcpy(newFriend->status, status);
    return newFriend;
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

void pushFriend(const char *name, const char *status) {
    Friend *temp = createFriend(name,status);

    if(!auth->headfriend) {
       auth->headfriend = auth->tailfriend = temp;
    }
    else {
        auth->tailfriend->next = temp;
        temp->prev = auth->tailfriend;
        auth->tailfriend = temp;
    }
}
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
    printf("Please type in your username[Lowercase] : ");
    char name[255];
    scanf("%s",&name);
    printf("Please type in your password[Lowercase] : ");
    char pass[255];
    scanf("%s",&pass);
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
        createUser(name,pass);
        pushUser(name,pass);
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
    while(cur){
        if(strcmp(cur->status,"Accepted")==0){
            printf("%d.         %s\n",cnt,cur->friendname);
            cnt++;
        }
        cur = cur->next;
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
            printf("--- You've logged out ---\n");
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); MainMenu();
    }
  
}
void addFriend(){
    system("cls");
    printf("[All User]\n");
    printf("No.        Username\n");
    User *cur = headuser;
    int cnt = 1;
    while(cur){
        if(strcmp(auth->username,cur->username)!=0){
            printf("%d.         %s\n",cnt,cur->username);
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
            found = true;
            break;
        }
        curr = curr->next;
    }
    if(found){
        createFriend(name,"Pending");
        pushFriend(name,"Pending");
        printf("--Your request has been sent to %s--\n",name);
        printf("Press Enter to Continue!\n");
        getchar(); getchar(); Dashboard();
    }else{
            printf("No user found!\n");
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); Dashboard();
    }
    

}
void removeFriend(){
    return;
}
void viewInbox(){
    system("cls");
    printf("[All Friend Requests of %s\n",auth->username);
    printf("No.        Username\n");
    User *cur = headuser;
    int cnt = 1;
    while(cur){
        bool cek = false;
        if(strcmp(auth->username,cur->username)!=0){
          Friend *curr = cur->headfriend;
          while(curr){
              if(strcmp(curr->friendname,auth->username)==0 && strcmp(curr->status,"Pending")==0){
                   printf("%d.         %s\n",cnt,cur->username);
                   cek = true;
                   break;
              }
              curr = curr->next;
          }
          if(cek) cnt++;
        }
         cur = cur->next;
    }
    printf("\n\n");
    if(cnt==1){
        printf("You don't have any inbox\n");
        printf("Press Enter to Continue!\n");
        getchar(); getchar(); Dashboard();
    }else{
    printf("Which user do you  want to be accepted ?\n");
    char name[255];
    scanf("%s", &name);
    printf("\n");
    User *cur1 = headuser;
    bool found = false;
    while(cur1) {
        if(strcmp(cur1->username, name) == 0 && strcmp(name,auth->username)!=0){
            Friend *curr1 = cur1->headfriend;
            while(curr1){
                if(strcmp(curr1->friendname,auth->username)==0){
                    strcpy(curr1->status,"Accepted");
                    found = true;
                    break;
                }
                curr1 = curr1->next;
            }
            if(found) break;
        }
        cur1 = cur1->next;
    }
    
        if(found){
            createFriend(name,"Accepted");
            pushFriend(name,"Accepted");
            printf("-- You accepted the request from %s --\n",name);
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); Dashboard();
        }else{
            printf("-- You accepted the request from %s --\n",name);
            printf("Press Enter to Continue!\n");
            getchar(); getchar(); Dashboard();
        }
    }

}
void viewSentRequest(){
    return;
}
void notes(){
    return;
}
int main(){
    MainMenu();
}