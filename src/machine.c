#include <stdio.h>  // for getc, printf
#include <stdlib.h> // malloc, free
#include "ijvm.h"
#include "util.h" // read this file for debug prints, endianness helper functions


// see ijvm.h for descriptions of the below functions

FILE *in;   // use fgetc(in) to get a character from in.
            // This will return EOF if no char is available.
FILE *out;  // use for example fprintf(out, "%c", value); to print value to out

void set_input(FILE *fp) 
{ 
  in = fp; 
}

void set_output(FILE *fp) 
{ 
  out = fp; 
}

typedef struct
  {
    uint32_t magic_num;
    uint32_t constant_ori;
    uint32_t constant_siz;
    uint32_t txt_size;
    uint32_t txt_ori;
    int32_t *constant_array;
    uint8_t *text_array;
  }  binary_data;

binary_data binary_dataa;

int init_ijvm(char *binary_path) 
{
  puts("test");
  in = stdin;
  out = stdout;

  FILE  *f = fopen(binary_path, "rb");
  uint8_t buff1[4];
  uint8_t buff2;

  fread(&buff1, sizeof(uint8_t), 4, f);
  uint32_t magic_number = read_uint32_t(buff1);
  binary_dataa.magic_num = magic_number;
  printf("magic size is %d", magic_number);

  fread(&buff1, sizeof(uint8_t), 4, f);
  uint32_t constant_origin = read_uint32_t(buff1);
  binary_dataa.constant_ori = constant_origin;

  fread(&buff1, sizeof(uint8_t), 4, f);
  uint32_t constant_size = read_uint32_t(buff1);
  binary_dataa.constant_siz = constant_size;

  binary_dataa.constant_array = (int32_t*) malloc(constant_size * sizeof(int32_t));

  for (int i = 0; i < constant_size/4; i++){
      fread(&buff1, sizeof(uint8_t), 4, f);
      binary_dataa.constant_array[i] = read_uint32_t(buff1);
      fprintf(stderr, "constant is nu : %d\n", binary_dataa.constant_array[i]);
  }

  fread(&buff1, sizeof(uint8_t), 4, f);
  uint32_t text_origin = read_uint32_t(buff1);
  binary_dataa.txt_ori = text_origin;


  fread(&buff1, sizeof(uint8_t), 4, f);
  uint32_t text_size = read_uint32_t(buff1);
  binary_dataa.txt_size = text_size;
  fprintf(stderr, "the text szie is : %d\n", text_size);

  binary_dataa.text_array = (uint8_t*) malloc(text_size * sizeof(uint8_t));

  for (int i = 0; i < text_size; i++){
      fread(&buff2, sizeof(uint8_t), 1, f);
      fprintf(stderr, "%x\n", buff2);
      binary_dataa.text_array[i] = buff2;
  }




// loop constant size/4 in een dynamic array met malloc 
// constant is int32     text uint8
  // fread(&buff1, sizeof(uint8_t), binary_dataa.constant_siz, f);
  // uint32_t constant_data = read_uint32_t(&buff1);
  // // binary_dataa.constant_dat = constant_data;



  // fread(&buff1, sizeof(uint8_t), constant_size, f);

  

  // TODO: implement me
  return 0;
}

void destroy_ijvm(void) 
{
  free (binary_dataa.constant_array);
  free (binary_dataa.text_array);
}

byte_t *get_text(void) 
{
  return binary_dataa.text_array;
}

unsigned int get_text_size(void) 
{
  return binary_dataa.txt_size;
}

word_t get_constant(int i) 
{
  return binary_dataa.constant_array[i];
}

unsigned int get_program_counter(void) 
{
  // TODO: implement me
  return 0;
}

word_t tos(void) 
{
  // this operation should NOT pop (remove top element from stack)
  // TODO: implement me
  return -1;
}

bool finished(void) 
{
  // TODO: implement me
  return false;
}

word_t get_local_variable(int i) 
{
  // TODO: implement me
  return 0;
}

void step(void) 
{
  // TODO: implement me

}

void run(void) 
{
  while (!finished()) 
  {
    step();
  }
}

byte_t get_instruction(void) 
{ 
  return get_text()[get_program_counter()]; 
}

// Below: methods needed by bonus assignments, see ijvm.h

//int get_call_stack_size(void) 
//{
   // TODO: implement me
//   return sp;
//}


// Checks if reference is a freed heap array. Note that this assumes that 
// 
//bool is_heap_freed(word_t reference) 
//{
   // TODO: implement me
// return 0;
//}
