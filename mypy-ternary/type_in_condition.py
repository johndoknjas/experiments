from typing import Union

def if_statement_example(param: Union[str, int]) -> bool:
    if isinstance(param, str):
        return len(param) == 2
    else:
        return param < 3
    
def ternary_example(param: Union[str, int]) -> bool:
    return len(param) == 2 if isinstance(param, str) else param < 3