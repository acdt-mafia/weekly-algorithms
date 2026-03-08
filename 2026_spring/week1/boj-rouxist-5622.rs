use std::io::{self, Read};

fn main() {
    // read entire stdin
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    // get the first token (e.g., "wa")
    let mut it = input.split_whitespace();
    let s = it.next().unwrap();


    // MAIN SCRIPT
    let mut ans: u8 = 0;

    for c in s.bytes() {
        let idx = c - b'A';

        let dial = match idx {
            0..=2 => 2,
            3..=5 => 3,
            6..=8 => 4,
            9..=11 => 5,
            12..=14 => 6,
            15..=18 => 7,
            19..=21 => 8,
            22..=25 => 9,
            _ => 0,
        };

        ans += dial + 1;
    }

    println!("{}", ans);
}