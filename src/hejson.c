#include "hejson.h"
//check memory call it after every malloc
inline static void check_memory(void *pointer){

    if (pointer == NULL)
        out_of_memory();

}

//SET A SIMPLE VALUE IN A DICT
static void set_simple_in_dict(Dict *new_object , int type_element , void *value ){

    new_object->type = SIMPLE;

    new_object->element.type = type_element;

    switch (new_object->element.type)
    {
    case INT:
        {
            int *value_int = (int *)value;
            new_object->element.obj_integer = *value_int;
        }
        break;
    case BOOL:
        {
            boolean *value_bool = (boolean *)value;
            new_object->element.obj_integer = *value_bool;
        }
        break;
    case DOUBLE:
        {
            double *value_double = (double *)value;
            new_object->element.obj_double = *value_double;
        }
        break;
    case NULL_:
        break;
    case STRING://i tipi string devon oessere deallocati apparte
        {
            new_object->element.obj_string = (char *)malloc(strlen((char *)value) + 1);
            strcpy(new_object->element.obj_string,(char *)value);
        }
        break;
    default:
        
        fprintf(stderr,"error in set_simple line\n");
        
        break;
    }

}

//SET A SIMPLE VALUE IN AN ARRAY
static void set_simple_in_array(Array *new_object , int type_element , void *value )
{

    new_object->type = SIMPLE;

    new_object->element.type = type_element;

    switch (new_object->element.type)
    {
    case INT:
        {
            int *value_int = (int *)value;
            new_object->element.obj_integer = *value_int;
        }
        break;
    case BOOL:
        {
            boolean *value_bool = (boolean *)value;
            new_object->element.obj_integer = *value_bool;
        }
        break;
    case DOUBLE:
        {
            double *value_double = (double *)value;
            new_object->element.obj_double = *value_double;
        }
        break;
    case NULL_:
        break;
    case STRING://i tipi string devon oessere deallocati apparte
        {
            new_object->element.obj_string = (char *)malloc(strlen((char *)value) + 1);
            strcpy(new_object->element.obj_string,(char *)value);
        }
        break;
    default:
        
        fprintf(stderr,"error in set_simple line\n");
        
        break;
    }

}

//SET THE KEY IN A DICT
inline static void set_key(Dict *new_object,const char *key)
{

    size_t i = 0;
    while (i  < strlen(key) + 1)
    {
        new_object->key[i] = key[i];
        i++;
    }

}

//SET GENERIC SIMPLE IN A GENERIC STRUCTURE
static void set_simple(void *new_object_generic , int type_element , void *value , int type_structure)
{

    switch (type_structure)
    {
    case DICT:
        
        set_simple_in_dict((Dict *)new_object_generic, type_element , value);
        
        break;

    case ARRAY:
        
        set_simple_in_array((Array *)new_object_generic, type_element , value);
        
        break;
    }

}

//push_on_a_dict_a_simple_value
Dict *push_on_dict_a_simple(Dict **head , void *value , const char *key , int type_simple)
{

    Dict *new_object = (Dict *)malloc(sizeof(Dict) + strlen(key) + 1);    
    
    check_memory((void *)new_object);
    
    set_simple((void *)new_object  , type_simple , value , DICT);

    set_key(new_object , key);

    new_object->next_element = *head;
    
    if (*head != NULL)
    {
        (*head)->previous_element = new_object;
    }
    
    *head = new_object;

    return *head;

}

//push on dicy a struct object
Dict *push_on_dict_struct(Dict **head, int type)
{

    Dict *new_object = (Dict *)malloc(sizeof(Dict));

    check_memory(new_object);

    switch (type)
    {
    case ARRAY:
        new_object->new_array = NULL;
        new_object->type = ARRAY;
        break;
    
    case DICT:
        new_object->new_head = NULL;
        new_object->type = DICT;
        break;
    }


    new_object->next_element = (*head);

    if (*head != NULL)
        (*head)->previous_element = new_object;
    
    (*head) = new_object;


    return *head;

}

//push_on_array_a_simple_value
Array *push_on_array_simple(Array **head , void *value , int type_simple)
{

    Array *new_object = (Array *)malloc(sizeof(Array));    
    
    check_memory((void *)new_object);

    set_simple(new_object, type_simple , value , ARRAY);    

    new_object->next_element = *head;
    
    if (*head != NULL)
    {
        (*head)->previous_element = new_object;
    }
    
    *head = new_object;

    return *head;


}

//PUSH on array struct object
Array *push_on_array_a_struct(Array **head , int type)
{

    Array *new_object = (Array *)malloc(sizeof(Array));    
    
    check_memory(new_object);
    
    switch (type)
    {
    case ARRAY:
        new_object->new_head = NULL;
        new_object->type = ARRAY;
        break;
    
    case DICT:
        new_object->new_dict_head = NULL;
        new_object->type = DICT;
        break;
    }


    new_object->next_element = (*head);

    if (*head != NULL)
        (*head)->previous_element = new_object;

    (*head) = new_object;

    return *head;

}


Json *alloc_simple(int type)
{
    Json *new = (Json *)malloc(sizeof(Json));
    check_memory((void *)new);

    new->type =SIMPLE;
    
    switch (type)
    {
    case STRING:
        new->new_simple_object.type = STRING;
        break;
    case INT:
        new->new_simple_object.type = INT;
        break;
    case DOUBLE:
        new->new_simple_object.type = DOUBLE;
        break;
    case NULL_:
        new->new_simple_object.type = NULL_;
        break;
    case BOOL:
        new->new_simple_object.type = BOOL;
        break;
    default:
        printf("error in alloc_simple type not correct\n");
        exit(EXIT_FAILURE);
    }
    return new;

}

Json *alloc_struct_object(int type)
{

    Json *new = (Json *)malloc(sizeof(Json));
    switch (type)
    {
    case ARRAY:
        new->type = ARRAY;
        new->new_array = NULL;
        break;
    
    case STRING:
        new->type = DICT;
        new->new_dict = NULL;
        break;
    }
    
    return new;

}

//dealloc of a array
void dealloc_array(Array **array_head_ref)
{

    Array *current = *array_head_ref;
    Array *tmp = current;

    while (current!=NULL)
    {

        current = tmp->next_element;
        
        if (tmp->type == SIMPLE)
        {   
            if((*tmp).element.type == STRING)  
                free((*tmp).element.obj_string);
        }
        else if(tmp->type == DICT){

            dealloc_dict(&(tmp->new_dict_head));

        }
            
        else if(tmp->type == ARRAY)
        {
         
            dealloc_array(&(tmp->new_head));
        
        }   
        
        free(tmp);
        
        tmp = current;
    }

}

//dealloc of a dict
void dealloc_dict(Dict **dict_head_ref)
{

    Dict *current = *dict_head_ref;
    Dict *tmp = current;
    
    while (current!=NULL)
    {

        current = tmp->next_element;
        
        if (tmp->type == SIMPLE)
        {
            if((*tmp).element.type == STRING)  
                free((*tmp).element.obj_string);
        }
        else if(tmp->type == DICT)
            dealloc_dict(&(tmp->new_head));
        else if(tmp->type == ARRAY)
            dealloc_array(&(tmp->new_array));
            
        
        free(tmp);
        
        tmp = current;
    }
    

}


void dealloc(Json **json_head_ref)
{

    switch ((*json_head_ref)->type)
    {
        case SIMPLE:
            
            if((*json_head_ref)->new_simple_object.type == STRING)  
                free((*json_head_ref)->new_simple_object.obj_string);

            break;

        case DICT:

            dealloc_dict(&((*json_head_ref)->new_dict));

            break;

        case ARRAY:

            dealloc_array(&((*json_head_ref)->new_array));

            break;
    }

    free(*json_head_ref);

}



inline static FILE *open_file(const char *filename){

    FILE *pr = fopen(filename,"r");
    if (pr == NULL)
    {
        perror("Error file not found\n");
        exit(EXIT_FAILURE);
    }
    return pr;
}

static Json *parse_null(FILE *pr){

    char token[5];
    token[0] = 'n';
    for (size_t i = 1; i < 4; i++)
    {
        token[i] = fgetc(pr);
    }
    token[4] ='\0';
    if (strcmp("null",token))
    {
        parse_error(token);
    }


    return alloc_simple(NULL_);
    
}

static Json *parse_boolean(FILE *pr,Json **json,char first){

    size_t size;

    if (first == 't')
        size = 4;
    else
        size = 5;

    char token[6];

    token[0] = first;

    for (size_t i = 1; i < size; i++)
        token[i] = fgetc(pr);
    
    token[size] = '\0';

    if (strcmp(token,"true") == 0)
    {
        *json = alloc_simple(BOOL);
        (*json)->new_simple_object.obj_bool = true;
    }else if(strcmp(token,"false") == 0)
    {
        *json = alloc_simple(BOOL);
        (*json)->new_simple_object.obj_bool = false;  
    }else
        parse_error(token);
    
    return *json;
}

Json *Json_parse(const char *filename){
    
    Json *json;
    
    FILE *pr = open_file(filename);
    
    char c = fgetc(pr);
    switch (c)
    {
    case '{':
        /* code */
        break;
    case '[':
        break;
    case 'n':
        json = parse_null(pr);
        break;
    case 't':
    case 'f':
        parse_boolean(pr, &json, c);
        break;
    default:
        if(isspace(c))
            break;
        if (isdigit(c) || '-')
        {
            
            break;
        }

        
    }
    
    fclose(pr);

    return json;

}


