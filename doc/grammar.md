_Main entry node_   [main]      ->      [stmt]*                 _Any amount of statement nodes_


_Statement node_    [stmt]      ->      { exit([expr]);         _Exit node_
                                        return [expr];        _Return statement_
                                        type ident = [expr];  _Variable declaration_


_Expression node_   [expr]      ->      { \_int                 _Integer_
                                        ident                 _Variable Identifier_

