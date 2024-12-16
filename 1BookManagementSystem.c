#include <stdlib.h> //for free
#include <stdio.h>
#include <string.h>
#include <ctype.h>   //add for toLowerCase

//Struct Definition
typedef struct BookManagementSystem {
    int bookID;
    char book_Name[20];
    char author_Name[20];
    char category[20];
    double price;
    double rating;
} BookManagementSystem;

int hardCoded(BookManagementSystem* book, int* ctr);
void storeBook(BookManagementSystem* book, int* ctr, int* size);
void displayAllBook(BookManagementSystem* book, int ctr);
void deleteBook(BookManagementSystem* book, int* ctr, int ind);
void updatePriceAndRating(BookManagementSystem* book, int ctr);
void sortBooks(BookManagementSystem* book, int ctr);
void displayTopBooks(BookManagementSystem* book, int ctr);
int searchByID(BookManagementSystem* book, int ctr, int id);
void searchByName(BookManagementSystem* book, int ctr, const char* name);
void search(BookManagementSystem* book, int ctr);
void searchByAuthor(BookManagementSystem* book, int ctr, const char* author);
void searchByCategory(BookManagementSystem* book, int ctr, const char* category);
void displayOneBook(BookManagementSystem* book, int index);
void toLowerCase(char* str);

int main() {
    int size = 20;
    BookManagementSystem* book = (BookManagementSystem*)malloc(size * sizeof(BookManagementSystem));
    if (book == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int ctr = 0;
    ctr = hardCoded(book, &ctr);
    printf("\nNumber of books after hard coding: %d\n", ctr);

    if (ctr > 0) {
        printf("\nDisplaying all hardcoded books:\n");
        displayAllBook(book, ctr);
    } else {
        printf("\nNo books available to display.\n");
    }

    int ch;
    do {
        printf("\n1. Add Book");
        printf("\n2. Display All Book");
        printf("\n3. Search Book");
        printf("\n4. Delete Book");
        printf("\n5. Update Price and Rating");
        printf("\n6. Sort Book");
        printf("\n7. Display Top 3 Books by Price and Rating");
        printf("\n8. Search by Author");
        printf("\n9. Search by Category");
        printf("\n0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            storeBook(book, &ctr, &size);
            break;

        case 2:
            if (ctr > 0) {
                displayAllBook(book, ctr);
            } else {
                printf("No book present!\n");
            }
            break;

        case 3:
            search(book, ctr);
            break;

        case 4: {
            int id;
            printf("\nEnter Book ID you want to delete: ");
            scanf("%d", &id);
            int i = searchByID(book, ctr, id);
            if (i == -1) {
                printf("\nBook not found!\n");
            } else {
                deleteBook(book, &ctr, i);
                printf("\nBook deleted successfully!\n");
            }
            break;
        }

        case 5:
            if (ctr != 0) {
                updatePriceAndRating(book, ctr);
            } else {
                printf("No books to update!\n");
            }
            break;

        case 6:
            if (ctr != 0) {
                sortBooks(book, ctr);
                printf("\nBooks sorted by Book ID!\n");
            } else {
                printf("No books to sort!\n");
            }
            break;

        case 7:
            if (ctr >= 3) {
                displayTopBooks(book, ctr);
            } else {
                printf("Not enough books to display top 3!\n");
            }
            break;

        case 8:
            if (ctr != 0) {
                char author[20];
                printf("\nEnter Author's Name: ");
                scanf("%s", author);
                searchByAuthor(book, ctr, author);
            } else {
                printf("No books available!\n");
            }
            break;

        case 9:
            if (ctr != 0) {
                char category[20];
                printf("\nEnter Category: ");
                scanf("%s", category);
                searchByCategory(book, ctr, category);
            } else {
                printf("No books available!\n");
            }
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please enter a valid option.\n");
            break;
        }

    } while (ch != 0);

    free(book);
    return 0;
}

void displayTopBooks(BookManagementSystem* book, int ctr) {
    int i, j;
    // Sort books by price and rating in descending order
    for (i = 0; i < ctr - 1; i++) {
        for (j = 0; j < ctr - i - 1; j++) {
            if (book[j].price < book[j + 1].price ||
                (book[j].price == book[j + 1].price && book[j].rating < book[j + 1].rating)) {
                BookManagementSystem temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }

    printf("\nTop 3 Books by Price and Rating:\n");
    for (i = 0; i < 3 && i < ctr; i++) {
        displayOneBook(book, i);
    }
}

int hardCoded(BookManagementSystem* book, int* ctr) {
    book[*ctr].bookID = 101;
    strcpy(book[*ctr].book_Name, "Shrimanyogi");
    strcpy(book[*ctr].author_Name, "Ranjit Desai");
    strcpy(book[*ctr].category, "Historical Fiction");
    book[*ctr].price = 450.00;
    book[*ctr].rating = 4.8;
    (*ctr)++;

    book[*ctr].bookID = 102;
    strcpy(book[*ctr].book_Name, "Yugandhar");
    strcpy(book[*ctr].author_Name, "Shivaji Sawant");
    strcpy(book[*ctr].category, "Mythological");
    book[*ctr].price = 550.00;
    book[*ctr].rating = 4.7;
    (*ctr)++;

    book[*ctr].bookID = 103;
    strcpy(book[*ctr].book_Name, "Mrutyunjay");
    strcpy(book[*ctr].author_Name, "Shivaji Sawant");
    strcpy(book[*ctr].category, "Mythological");
    book[*ctr].price = 500.00;
    book[*ctr].rating = 4.9;
    (*ctr)++;

    book[*ctr].bookID = 104;
    strcpy(book[*ctr].book_Name, "Purnachandra");
    strcpy(book[*ctr].author_Name, "Sane Guruji");
    strcpy(book[*ctr].category, "Biography");
    book[*ctr].price = 300.00;
    book[*ctr].rating = 4.6;
    (*ctr)++;

    book[*ctr].bookID = 105;
    strcpy(book[*ctr].book_Name, "Batatyachi Chaal");
    strcpy(book[*ctr].author_Name, "P L Deshpande");
    strcpy(book[*ctr].category, "Humor");
    book[*ctr].price = 200.00;
    book[*ctr].rating = 4.8;
    (*ctr)++;

    book[*ctr].bookID =106;
    strcpy(book[*ctr].book_Name, "Tin Mule");
    strcpy(book[*ctr].author_Name, "Sane Guruji");
    strcpy(book[*ctr].category, "Mythological");
    book[*ctr].price =180.00;
    book[*ctr].rating = 4.6;
    (*ctr)++;

    book[*ctr].bookID =107;
    strcpy(book[*ctr].book_Name, "Agnipankh");
    strcpy(book[*ctr].author_Name, "A.P.J. Abdul Kalam");
    strcpy(book[*ctr].category, "Biopic");
    book[*ctr].price =400.00;
    book[*ctr].rating = 4.9;
    (*ctr)++;

    return *ctr;
}

void storeBook(BookManagementSystem* book, int* ctr, int* size) {
    if (*ctr >= *size) {
        *size *= 2;
        BookManagementSystem* temp = (BookManagementSystem*)realloc(book, *size * sizeof(BookManagementSystem));
        if (temp == NULL) {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
        book = temp;
    }

    printf("Enter Book ID: ");
    scanf("%d", &(book[*ctr].bookID));

    printf("Enter Book name: ");
    scanf("%s", book[*ctr].book_Name);

    printf("Enter Author Name: ");
    scanf("%s", book[*ctr].author_Name);

    printf("Enter Category: ");
    scanf("%s", book[*ctr].category);

    printf("Enter Price: ");
    scanf("%lf", &(book[*ctr].price));

    printf("Enter Rating: ");
    scanf("%lf", &(book[*ctr].rating));

    printf("\nBook added successfully!\n");
    (*ctr)++;
}

void displayAllBook(BookManagementSystem* book, int ctr) {
    int i;
    if (ctr > 0) {
        printf("\n+---------+------------------+-------------------+---------------------+----------------+---------------+");
        printf("\n| Book ID |     Book name    |    Book Author    |    Book Category    |   Book Price   |  Book Rating  |");
        printf("\n+---------+------------------+-------------------+---------------------+----------------+---------------+\n");

        for (i = 0; i < ctr; i++) {
            printf("|%8d |%17s |%18s |%20s |%15.2lf |%14.1lf |\n",
                   book[i].bookID, book[i].book_Name, book[i].author_Name, book[i].category, book[i].price, book[i].rating);
        }

        printf("+---------+------------------+-------------------+---------------------+----------------+---------------+\n");
    } else {
        printf("\nNo books to display!\n");
    }
}

void deleteBook(BookManagementSystem* book, int* ctr, int ind) {
    int i;
    for (i = ind; i < *ctr - 1; i++) {
        book[i] = book[i + 1];
    }
    (*ctr)--;
}

void updatePriceAndRating(BookManagementSystem* book, int ctr) {
    int id;
    printf("\nEnter Book ID to update Price and Rating: ");
    scanf("%d", &id);
    int i = searchByID(book, ctr, id);
    if (i == -1) {
        printf("\nBook not found!\n");
        return;
    }

    printf("Enter new Price: ");
    scanf("%lf", &book[i].price);

    printf("Enter new Rating: ");
    scanf("%lf", &book[i].rating);

    printf("\nPrice and Rating updated successfully!\n");
}

void searchByAuthor(BookManagementSystem* book, int ctr, const char* author) {
    char lowerAuthor[20];
    strcpy(lowerAuthor, author);
    toLowerCase(lowerAuthor);
    int i, found = 0;

    for (i = 0; i < ctr; i++) {
        char lowerBookAuthor[20];
        strcpy(lowerBookAuthor, book[i].author_Name);
        toLowerCase(lowerBookAuthor);
        if (strstr(lowerBookAuthor, lowerAuthor) != NULL) {
            displayOneBook(book, i);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo books found by this author!\n");
    }
}

void searchByCategory(BookManagementSystem* book, int ctr, const char* category) {
    char lowerCategory[20];
    strcpy(lowerCategory, category);
    toLowerCase(lowerCategory);
    int i, found = 0;

    for (i = 0; i < ctr; i++) {
        char lowerBookCategory[20];
        strcpy(lowerBookCategory, book[i].category);
        toLowerCase(lowerBookCategory);
        if (strstr(lowerBookCategory, lowerCategory) != NULL) {
            displayOneBook(book, i);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo books found in this category!\n");
    }
}

void sortBooks(BookManagementSystem* book, int ctr) {
    int i, j;
    for (i = 0; i < ctr - 1; i++) {
        for (j = 0; j < ctr - i - 1; j++) {
            if (book[j].bookID > book[j + 1].bookID) {
                BookManagementSystem temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }
}

int searchByID(BookManagementSystem* book, int ctr, int id) {
    int i;
    for (i = 0; i < ctr; i++) {
        if (book[i].bookID == id) {
            return i;
        }
    }
    return -1;
}

void toLowerCase(char* str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void searchByName(BookManagementSystem* book, int ctr, const char* name) {
    char lowerName[20];
    strcpy(lowerName, name);
    toLowerCase(lowerName);

    int found = 0, i;

    for (i = 0; i < ctr; i++) {
        char lowerBookName[20];
        strcpy(lowerBookName, book[i].book_Name);
        toLowerCase(lowerBookName);

        if (strstr(lowerBookName, lowerName) != NULL) {
            if (!found) {
                printf("\nBooks Found! Details are as follows:\n");
                found = 1;
            }
            displayOneBook(book, i);
        }
    }

    if (!found) {
        printf("\nNo matching books found!\n");
    }
}

void search(BookManagementSystem* book, int ctr) {
    int id;
    char name[20];
    printf("Search by:\n1. Book ID\n2. Book Name\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        printf("Enter Book ID: ");
        scanf("%d", &id);
        int index = searchByID(book, ctr, id);
        if (index != -1) {
            displayOneBook(book, index);
        } else {
            printf("\nBook not found!\n");
        }
        break;
    case 2:
        printf("Enter Book Name: ");
        scanf("%s", name);
        searchByName(book, ctr, name);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}

void displayOneBook(BookManagementSystem* book, int index) {
    printf("\n+---------+------------------+-------------------+---------------------+----------------+---------------+");
    printf("\n| Book ID |     Book name    |    Book Author    |    Book Category    |   Book Price   |  Book Rating  |");
    printf("\n+---------+------------------+-------------------+---------------------+----------------+---------------+\n");
    printf("|%8d |%17s |%18s |%20s |%15.2lf |%14.1lf |\n",
           book[index].bookID, book[index].book_Name, book[index].author_Name, book[index].category, book[index].price, book[index].rating);
    printf("+---------+------------------+-------------------+---------------------+----------------+---------------+\n");
}