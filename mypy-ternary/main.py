from typing import Union, List

def get_str_float(b: bool) -> Union[str, float]:
    return 8 if b else '8' # mypy gives no error here

def get_list(b: bool) -> Union[List[str], List[List[str]]]:
    return ['a'] if b else [['a']]
    """
    Mypy gives no error if I replace the above line with the following:
    if b:
        return ['a']
    else:
        return [['a']]
    """

def main():
    print(get_list(True))
    print(get_str_float(True))

if __name__ == "__main__":
    main()