import sys
from utils import file_utils
import os
import importlib

if __name__ == '__main__':
    day = sys.argv[1]
    problem_no = sys.argv[2]
    day_path = os.getcwd() + '/day' + day + '/'

    #appending the day folder so that modules inside the particular day folder can be used
    sys.path.append(day_path)

    #importing the required module from the particular day and then creating object for the required class
    day_module = importlib.import_module('day' + day + '.problem_' + problem_no)
    solution_object = getattr(day_module, 'Solution' + day + problem_no)()

    file_utils.read_file(day_path + 'data.txt', solution_object.line_reader, solution_object.process_data)
