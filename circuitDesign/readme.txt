
in this project, the circuits are specified with  a series of directives. These directives refer to various
named variables, which correspond to wires in a circuit diagram. Many of the directives describe a
logic gate or similar building block, indicating which varibles correspond to its input and output.
Each directive has the form of a name followed by one or more parameters, separated by
whitespace. The name indicates which directive and determines the number of parameters. Some
directives take a variable number of parameters; their first parameter will always be an integer which
is used to determine the number of parameters. Depending on the directive, some parameters will
be inputs and some will be outputs.
Variables in a circuit can be classified into three non-overlapping sets. Input variables must be
declared by the INPUT directive, and may only occur as input parameters. Output variables must be
declared by the OUTPUT directive and may occur exactly once in an output parameter. All other
variables are temporary variables and must occur exactly once as an output parameter and zero or
more times as an input parameter.
A variable name consists of a letter followed by zero or more letters or digits.the variable names are no longer than 16 characters.
In addition to variables, the constant inputs 0 and 1 may be used as input parameters. These
are always false and always true, respectively.
Finally, directives may allow an optional colon (:) to occur between certain parameters. The
presence or absence of this colon has no effect on semantics, but may make the specification more
readable.
