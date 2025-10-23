#include<string.h>
#include<stdio.h>

#define MAX_BOOKS 100
#define MAX_STUDENTS 100
#define MAX_ISSUED_PER_STUDENT 3
#define MAX_ISSUED 100

struct Book{
	int id;
	char title[50];
	char author[50];
	int quantity;
};

struct Student{
	int id;
	char name[50];
};

struct IssuedBook{
	int studentId;
	int bookId;
	char issueDate[20];
};

struct Book books[MAX_BOOKS];
int bookCount=0;

struct Student students[MAX_STUDENTS];
int studentCount=0;

struct IssuedBook issuedBooks[MAX_ISSUED];
int issuedCount=0;


void displayMenu();
void addBook();
void viewBooks();
void registerStudent();
void issueBook();
void returnBook();
void viewIssuedBooks();

int findBookIndex(int bookId);
int findStudentIndex(int studentId);
int countIssuedToStudent(int studentId);


int main(){
	
	
	
	while(1){
		displayMenu();
		int choice;
	printf("Enter your choice ");
	scanf("%d" , &choice);
		switch(choice){
			case 1:{
			addBook();
			break;
		}
		case 2:{
			viewBooks();
			break;
		}
		case 3:{
			registerStudent();
			break;
		}
		case 4:{
			issueBook();
			break;
		}
		case 5:{
			returnBook();
			break;
		}
		case 6:{
			viewIssuedBooks();
			break;
		}
		case 7:{
			printf("Exiting Program. GoodBye!\n");
			return 0;
		}
		default:{
			printf("Invalid Choice. Try Again.\n");
			break;
		}
		}
		
	}
	return 0;
}

void displayMenu(){
	printf("\n--- LIBRARY MENU ---\n");
	printf("1. Add Book\n");
	printf("2. View Books\n");
	printf("3. Register Student\n");
	printf("4. Issue Book\n");
	printf("5. Return Book\n");
	printf("6. View Issued Books\n");
	printf("7. Exit\n");
}

void addBook(){
	struct Book b;
	printf("Enter Book ID: ");
	scanf("%d", &b.id);
	getchar();
	printf("Enter Title: ");
	scanf(" %[^\n]", b.title);
	printf("Enter Author: ");
	scanf(" %[^\n]", b.author);
	printf("Enter Quantity: ");
	scanf("%d", &b.quantity);
	
books[bookCount++] = b;
printf("Book added successfully!\n");
}

void viewBooks(){
	printf("\n--- Book List---\n");
	for(int i=0;i<bookCount;i++){
		printf("ID: %d | Title: %s | Author: %s | Quantity:%d\n", books[i].id,books[i].title,books[i].author,books[i].quantity);
	}
}

void registerStudent(){
	struct Student s;
	printf("Enter Student ID: ");
	scanf("%d", &s.id);
	getchar();
	printf("Enter name: ");
	scanf(" %[^\n]" ,s.name );
	
	students[studentCount++] = s;
	printf("Student Registered Successfully!\n");
}

void issueBook(){
	int sid, bid;
	printf("Enter Student ID: ");
	scanf("%d", &sid);
	int issuedToStudent= countIssuedToStudent(sid);
	if(issuedToStudent>=MAX_ISSUED_PER_STUDENT){
		printf("Student has already issued maximum number of books (3).\n");
		return;
	}
	
	printf("Enter Book ID to issue: ");
	scanf("%d", &bid);
	
	int bIndex = findBookIndex(bid);
	if(bIndex==-1 || books[bIndex].quantity<=0){
		printf("Book Not Available.\n");
		return;
	}

struct IssuedBook ib;
ib.studentId=sid;
ib.bookId=bid;
getchar();
printf("Enter Issue Date(e.g. 2025-10-22): ");
scanf(" %[^\n]", ib.issueDate);

books[bIndex].quantity--;
issuedBooks[issuedCount++]=ib;

printf("Book Issued Successfully!\n");
}

int countIssuedToStudent(int studentId){
	int count=0;
	for(int i=0;i<issuedCount;i++){
		if(issuedBooks[i].studentId==studentId) count++;
	}
	return count;
}

int findBookIndex(int bookId){
	for(int i=0;i<bookCount;i++){
		if(books[i].id==bookId) return i;
	}
	return -1;
}


int findStudentIndex(int studentId){
	for(int i=0;i<studentCount;i++){
		if(students[i].id==studentId) return i;
	}
	return -1;
}

void returnBook(){
	int sid, bid;
	printf("Enter Student ID");
	scanf("%d", &sid);
	printf("Enter Book ID to return");
	scanf("%d", &bid);
	
	int found=0;
	for(int i=0;i<issuedCount;i++){
		if(issuedBooks[i].studentId==sid && issuedBooks[i].bookId==bid){
			
			for(int j=i;j<issuedCount-1;j++){
				issuedBooks[j]=issuedBooks[j+1];
			}
			issuedCount--;
			int bIndex=findBookIndex(bid);
			if(bIndex!=-1) books[bIndex].quantity++;
			printf("Book Returned Successfully!\n");
			found=1;
			break;
		}
		
	}
	if(!found){ 
	printf("Issued Record Not Found.\n");
	}
}

void viewIssuedBooks() {
	printf("\n--- Issued Books ---\n");
	for(int i=0;i<issuedCount;i++){
		printf("Student ID: %d | Book ID: %d | Issue Date: %s\n", issuedBooks[i].studentId, issuedBooks[i].bookId, issuedBooks[i].issueDate);
	}
}

