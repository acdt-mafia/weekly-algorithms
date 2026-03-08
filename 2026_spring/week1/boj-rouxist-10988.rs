use std::io::{self, Read};

struct Stack {
    data: Vec<char>,
}

impl Stack {
    fn new() -> Self {
        Stack { data: Vec::new() }
    }

    fn push(&mut self, value: char) {
        self.data.push(value);
    }

    fn pop(&mut self) -> Option<char> {
        self.data.pop()
    }
}


fn main() {
    // INPUT
    // read entire stdin
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    // get the first token
    let mut it = input.split_whitespace();
    let s = it.next().unwrap();
    
    
    // MAIN SCRIPT
    let mut stack = Stack::new();
    let mut output: i32 = 1;
    
    let length = s.len();
    let half_length = length / 2;
    
    for idx in 0..half_length {
        stack.push(s.chars().nth(idx).unwrap());
    }


    let mut start_idx = half_length;

    if length % 2==1 {
        start_idx += 1;
    }

    for idx in start_idx..length {
        let elem = stack.pop();
        if elem != Some(s.chars().nth(idx).unwrap()) {
            output = 0;
        }
    }
    println!("{}", output);
}