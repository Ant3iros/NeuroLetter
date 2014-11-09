#include "fann.h"

int main()
{
  struct fann *ann = fann_create_standard(1, 0.7, 3, 26, 13, 3);
  fann_train_on_file(ann, "frequencies.data", 200, 
		      10, 0.0001);
  fann_save(ann, "language_classify.net");
  fann_destroy(ann);
  return 0;
}
