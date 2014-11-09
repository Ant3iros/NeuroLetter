#include <stdio.h>

#include "fann.h"

int main()
{
  const unsigned int num_layers = 3;
  const unsigned int num_neurons_hidden = 95;

  struct fann *ann;
  struct fann_train_data *train_data, *test_data;

  unsigned int i = 0;

  printf("Creating network.\n");
  train_data = fann_read_train_from_file("/datasets/project.train");
  
  ann = fann_create_standard(num_layers, train_data->num_input,
			     num_neurons_hidden, train_data->num_output);

  printf("Training network.\n");
}
