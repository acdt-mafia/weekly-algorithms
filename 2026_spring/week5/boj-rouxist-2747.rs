use std::{io::{self, Read}};

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    
    let n: usize = lines.next().unwrap().parse().unwrap();

    
    // Main Script
    let mut dp: Vec<usize> = vec![0; n + 1];
    dp[1] = 1;

    for idx in 1..n {
        dp[idx+1] = dp[idx] + dp[idx-1];
    }

    println!("{}", dp[n]);
}