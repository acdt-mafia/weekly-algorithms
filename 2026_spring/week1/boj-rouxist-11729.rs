use std::io::{self, Read};

fn action(n: u32, a: i32, b: i32, c: i32, output: &mut String) {
    // a: starting rod, b: intermediary rod, c: destination rode
    if n == 1 {
        output.push_str(&format!("{} {}\n", a, c));
    } else {
        action(n-1, a, c, b, output);
        output.push_str(&format!("{} {}\n", a, c));
        action(n-1, b, a, c, output);
    }
}

fn main() {
    // INPUT
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let n: u32 = input.trim().parse().unwrap();
    
    
    // MAIN SCRIPT
    let mut output = String::new();
    output.push_str(&format!("{}\n", 2u32.pow(n) - 1));
    action(n, 1, 2, 3, &mut output);

    print!("{}", output);
}