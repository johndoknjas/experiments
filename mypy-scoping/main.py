def main() -> None:
    for i in (1,2):
        pass
    for i in ('a', 'b'):
        pass
    # However, the mypy error is by design: https://github.com/python/mypy/issues/9576

if __name__ == '__main__':
    main()