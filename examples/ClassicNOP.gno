public Attribute is interface {
    this enables read notify listen
};

public holon attribute {T is type; initial_value is T}: Attribute {
    public head is vertex T (new_val is T) new_val,
        this -> default when (this != this'), 
        initialise initial_value;
};

public Premise is interface {
    this enables read listen, disables write, is bool;
};

public holon {left is attribute} <> in {<, >, <=, >=, ==, !=} {right is same type as left},
             {left is same type as right} <> in {<, >, <=, >=, ==, !=} {right is Attribute},
             {left is Attribute} <> in {<, >, <=, >=, ==, !=} {right is same type as left, is Attribute} : Premise {
    public head is vertex bool bound left <> right,
        this -> default when (this != this');
};

public Condition is interface {
    this enables read listen, disables write, is bool;
};

public holon {left is in {Premise, bool}} <> in {&&, ||, ^^} {right is in {Premise, bool}}: Condition {
    public head is vertex bool bound left <> right,
        this -> default when (this != this');
};

public holon ! {op is in {Premise, bool}}: Condition {
    public this is vertex bool bound !right,
        this -> default when (this != this');
};

public holon condition {pr is in {Premise, bool}}: Condition {
    public this is vertex bool bound pr,
        this -> default when (this != this');
}

public Method is interface {
    public this enables notify
};

// Rule, Action and Instigation can be a holon directly because basically there is only one definition of them
// also, named holons are basically holons which fill an interface with identical specs


public Instigation is holon Instigation{mts... is Method} {
    public head is vertex, disables read,
    this notifies mts;
}

public  Action is holon Action{ins... is Instigation} {
    public head is vertex, disables read,
        this notifies ins;
}

public Rule is holon Rule{cd is Condition, act... is Action} {
    public head is vertex bool bound cd, enables listen,
        this notifies act when (cd != cd' && cd' = true);  
};



