

def read_file(file_name, input_parsing_function, processing_fn):
  with open(file_name) as fp:
    for line in fp:
      input_parsing_function(line)

  print(processing_fn())
