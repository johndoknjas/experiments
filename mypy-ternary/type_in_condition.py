from typing import Union

def if_statement_example(param: Union[str, int]) -> bool:
    if type(param) is str:
        return len(param) == 2
    else:
        return param < 3
    
def ternary_example(param: Union[str, int]) -> bool:
    return len(param) == 2 if type(param) is str else param < 3