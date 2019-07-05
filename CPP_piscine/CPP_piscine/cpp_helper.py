#!/usr/bin/python3

import argparse

def main(name=""):
    n = name
    name = name.lower()
    with open(n+'.hpp', 'w+') as f:
        f.write('#ifndef {}_HPP\n'.format(name.upper()))
        f.write('# define {}_HPP\n\n'.format(name.upper()))
        f.write('class {} {}\n\npublic:\n\n'.format(n, '{'))
        f.write('\t{}(void);\n'.format(n))
        f.write('\t{}(const {} &);\n'.format(n, n))
        f.write('\t~{}(void);\n'.format(n))
        f.write('\t{} & operator=(const {} &);\n'.format(n,n))
        f.write('\nprivate:\n\n};\n\n#endif')

    with open(n+'.cpp', 'w+') as f:
        f.write('#include "{}.hpp"\n\n'.format(n))
        f.write('{}::{}(void) {}\n'.format(n, n, '{'))
        f.write('\treturn;\n}\n\n')
        f.write('{}::{}(const {} &) {}\n'.format(n, n, n, '{'))
        f.write('\t*this = src;\n\treturn;\n}\n\n')
        f.write('{}::~{}(void) {}\n'.format(n, n, '{'))
        f.write('\treturn;\n}\n\n')
        f.write('{} & {}::operator=(const {} &) {}\n'.format(n, n, n, '{'))
        f.write('\treturn *this;\n}\n\n')

    print('{}.hpp & {}.cpp created.'.format(n, n))


if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "-c", "--classes", nargs='+', type=str,
        help="Class names to implements", default=None, required=True,
    )

    args = parser.parse_args()

    for c in args.classes:
        main(c)

    exit(0)
