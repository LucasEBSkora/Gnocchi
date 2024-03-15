public Attribute is interface {
    this enables read notify listen
};

public holon attribute(T is type, initial_value is T): Attribute {
    public head is vertex T (new_val is T) new_val,
        this -> default when (this != this'), 
        initialise initial_value;
};

public Premise is interface {
    this enables read listen, disables write, is bool, is bound;
};

public holon {left is Attribute} <> in {<, >, <=, >=, ==, !=} {right is Attribute} : Premise {
    public head is vertex bool bound left <> right,
        this -> default when (this != this');
};
