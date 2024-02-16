def optional_str() -> str | None:
    return ''

def accept_str(s: str) -> str:
    return s

def main() -> None:
    lst = [optional_str()]
    assert all(lst[i] is not None for i in range(0,1))
    print(accept_str(lst[0]))

if __name__ == '__main__':
    main()