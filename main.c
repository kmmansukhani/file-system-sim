#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct file {
    char *name;
    char *content;
} file;

typedef struct folder {
    char *name;
    struct folder **folders;
    struct file **files;
    int num_of_folders;
    int num_of_files;
} folder;

void print_current_folder(folder *parent) {
    int num_of_folders = parent->num_of_folders;
    int num_of_files = parent->num_of_files;

    for (int i = 0; i < num_of_folders; i++) {
        folder *f = (parent->folders)[i];
        printf("Folder: %s\n", f->name);
    }
    for (int i = 0; i < num_of_files; i++) {
        file *f = (parent->files)[i];
        printf("File: %s\n", f->name);
    }
}

void print_all(folder *parent, int level) {
    int num_of_folders = parent->num_of_folders;
    int num_of_files = parent->num_of_files;
    for (int i = 0; i < num_of_folders; i++) {
        folder *f = (parent->folders)[i];
        char *name_of_f = f->name;
        for (int j = 0; j < level; j++) {
            printf("    ");
        }
        printf("Folder: %s\n", name_of_f);
        if (f->num_of_folders > 0 || f->num_of_files > 0) {
            print_all(f, level + 1);
        }
    }

    // Prints all files
    for (int i = 0; i < num_of_files; i++) {
        for (int j = 0; j < level; j++) {
            printf("    ");
        }
        printf("File: %s\n", (parent->files)[i]->name);
    }
}

folder *create_folder(folder *parent, char *name) {
    // Initalizing new folder
    folder *new_folder = (folder *)(malloc(sizeof(folder)));
    new_folder->name = name;
    new_folder->folders = (folder **)(malloc(100 * sizeof(folder *)));
    new_folder->files = (file **)(malloc(100 * sizeof(file *)));
    new_folder->num_of_folders = 0;
    new_folder->num_of_files = 0;

    // Inserting folder into parent
    parent->folders[parent->num_of_folders] = new_folder;
    parent->num_of_folders++;
    return new_folder;
}

file *create_file(folder *parent, char *name, char *content) {
    // Initializing new file
    file *new_file = (file *)(malloc(sizeof(file)));
    new_file->name = name;
    new_file->content = content;
    parent->files[parent->num_of_files] = new_file;
    parent->num_of_files++;
    return new_file;
}

void free_all(folder *parent) {
    int num_of_folders = parent->num_of_folders;
    int num_of_files = parent->num_of_files;

    for (int i = 0; i < num_of_folders; i++) {
        folder *f = (parent->folders)[i];
        if (f->num_of_folders > 0) {
            free_all(f);
        }

        int num_of_files_f = f->num_of_files;
        for (int j = 0; j < num_of_files_f; j++) {
            file *fi = (f->files)[j];;
            printf("Deleting file %s\n", fi->name);
            free(fi);
            fi = NULL;
            f->num_of_files--;
        }
        printf("Deleting folder %s\n", f->name);
        parent->num_of_folders--;
        free(f);
        f = NULL;
    }
    for (int i = 0; i < num_of_files; i++) {
        file *fi = (parent->files)[i];
        printf("Deleting file %s\n", fi->name);
        free(fi);
        fi = NULL;
        parent->num_of_files--;
    };

};
folder *search_for_folder(folder *parent, char *name) {
    if (strcmp(parent->name, name) == 0) {
        return parent;
    }
    for (int i = 0; i < parent->num_of_folders; i++) {
        folder *result = search_for_folder((parent->folders)[i], name);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}

file *search_for_file(folder *parent, char *name) {
    for (int i = 0; i < parent->num_of_files; i++) {
        file *f = (parent->files)[i];
        if (strcmp(f->name, name) == 0) {
            return f;
        }
    }
    for (int i = 0; i < parent->num_of_folders; i++) {
        file *result = search_for_file((parent->folders)[i], name);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}

/*void interact() {
    printf("You are in the main folder\n");
    char response;
    int iters = 0;
    while (response != 'q') {
        printf("Press 1 to create a folder\n");
        printf("Press 2 to create a file\n");
        response = getchar();
        printf("\n");
        printf("%c\n", response);
        
    }
}*/

int main() {
    // Creating main folder
    folder *main_folder = (folder *)(malloc(sizeof(folder)));
    main_folder->name = "Main";
    main_folder->folders = (folder **)(malloc(100 * sizeof(folder *)));
    main_folder->files = (file **)(malloc(100 * sizeof(file *)));
    main_folder->num_of_folders = 0;
    main_folder->num_of_files = 0;

    print_all(main_folder, 0);
    free_all(main_folder);
    //interact();
    return 0;
}
