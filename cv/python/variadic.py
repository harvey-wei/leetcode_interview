def foo(f):
    def in_fun(*args, **kwargs):
        print(args)
        print(kwargs)

    return in_fun


@foo
def add(a, b):
    return a + b


if __name__ == '__main__':
    add(1, 2)
