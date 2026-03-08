use std::io::{self, Read};

// struct Stack<T> {
//     data: Vec<T>,
// }

struct Stack {
    data: Vec<i32>,
}

impl Stack {
    fn new() -> Self {
        Stack { data: Vec::new() }
    }

    fn push(&mut self, value: i32) {
        self.data.push(value);
    }

    fn pop(&mut self) -> Option<i32> {
        self.data.pop()
    }

    fn top(&self) -> Option<&i32> {
        self.data.last()
    }

    fn size(&self) -> usize {
        self.data.len()
    }

    fn is_empty(&self) -> bool {
        self.data.is_empty()
    }
}

fn main() {
    // INPUT
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let n: usize = it.next().unwrap().parse().unwrap();


    // MAIN SCRIPT
    let mut stack = Stack::new();
    let mut output = String::new();

    for _ in 0..n {
        let cmd = it.next().unwrap();

        match cmd {
            "push" => {
                let x: i32 = it.next().unwrap().parse().unwrap();
                stack.push(x);
            }
            
            "top" => {
                match stack.top() {
                    Some(v) => output.push_str(&format!("{}\n", v)),
                    None => output.push_str("-1\n"),
                }
            }
            
            "size" => {
                output.push_str(&format!("{}\n", stack.size()));
            }

            "empty" => {
                output.push_str(if stack.is_empty() { "1\n" } else { "0\n" });
            }

            "pop" => {
                match stack.pop() {
                    Some(v) => output.push_str(&format!("{}\n", v)),
                    None => output.push_str("-1\n"),
                }
            }

            _ => {}
        }
    }
    print!("{}", output);
}