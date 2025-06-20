mod solution {
    type Data = u64;
    const BUFSIZE: usize = 8192;
    const FILENAME: &str = "";

    use crate::solution::segment_tree::SegmentTree;
    use std::io::{self, BufRead, BufReader, BufWriter, Write};

    mod segment_tree {
        use crate::solution::Data;

        #[derive(Debug, Copy, Clone)]
        struct SegNode {
            sum: Data,
            add_lzy: Data,
            mul_lzy: Data,
        }

        pub struct SegmentTree {
            data: Vec<SegNode>,
            n: usize,
            p: Data,
        }

        impl SegmentTree {
            //private implement
            fn out_of_range(l: usize, r: usize, tar_l: usize, tar_r: usize) -> bool {
                r < tar_l || l > tar_r
            }

            fn in_range(l: usize, r: usize, tar_l: usize, tar_r: usize) -> bool {
                tar_l <= l && r <= tar_r
            }

            fn pull_up(&mut self, idx: usize) {
                debug_assert!(self.data.len() >= idx);
                self.data[idx].sum =
                    (self.data[idx << 1].sum + self.data[idx << 1 | 1].sum) % self.p;
            }

            fn push_down(&mut self, idx: usize, l: usize, r: usize) {
                debug_assert!(self.data.len() >= idx);

                let mid = l + (r - l) / 2;
                //mul firstly and add secondly
                //new_node_val == origin_val * mul_lzy_1 * mul_lzy_2 + add_lzy * mul_lzy_2 + add_lzy_2
                self.make_mul(idx << 1, self.data[idx].mul_lzy);
                self.make_add(idx << 1, l, mid, self.data[idx].add_lzy);

                self.make_mul(idx << 1 | 1, self.data[idx].mul_lzy);
                self.make_add(idx << 1 | 1, mid + 1, r, self.data[idx].add_lzy);

                self.data[idx].add_lzy = 0;
                self.data[idx].mul_lzy = 1;
            }

            fn make_add(&mut self, idx: usize, l: usize, r: usize, val: Data) {
                debug_assert!(self.data.len() >= idx);
                self.data[idx].sum += val * (r - l + 1) as Data;
                self.data[idx].sum %= self.p;
                self.data[idx].add_lzy += val;
                self.data[idx].add_lzy %= self.p;
            }

            fn make_mul(&mut self, idx: usize, val: Data) {
                debug_assert!(self.data.len() >= idx);
                self.data[idx].sum *= val;
                self.data[idx].sum %= self.p;
                self.data[idx].add_lzy *= val;
                self.data[idx].add_lzy %= self.p;
                self.data[idx].mul_lzy *= val;
                self.data[idx].mul_lzy %= self.p;
            }

            fn _ask(&mut self, idx: usize, l: usize, r: usize, tar_l: usize, tar_r: usize) -> Data {
                if Self::out_of_range(l, r, tar_l, tar_r) {
                    return 0;
                }
                if Self::in_range(l, r, tar_l, tar_r) {
                    return self.data[idx].sum;
                }
                self.push_down(idx, l, r);
                let mid = l + (r - l) / 2;
                (self._ask(idx << 1, l, mid, tar_l, tar_r)
                    + self._ask(idx << 1 | 1, mid + 1, r, tar_l, tar_r))
                    % self.p
            }

            fn _add(
                &mut self, idx: usize, l: usize, r: usize, tar_l: usize, tar_r: usize, val: Data,
            ) {
                if Self::out_of_range(l, r, tar_l, tar_r) {
                    return;
                }
                if Self::in_range(l, r, tar_l, tar_r) {
                    self.make_add(idx, l, r, val);
                    return;
                }
                let mid = l + (r - l) / 2;
                self.push_down(idx, l, r);
                self._add(idx << 1, l, mid, tar_l, tar_r, val);
                self._add(idx << 1 | 1, mid + 1, r, tar_l, tar_r, val);
                self.pull_up(idx);
            }

            fn _mul(
                &mut self, idx: usize, l: usize, r: usize, tar_l: usize, tar_r: usize, val: Data,
            ) {
                if Self::out_of_range(l, r, tar_l, tar_r) {
                    return;
                }
                if Self::in_range(l, r, tar_l, tar_r) {
                    self.make_mul(idx, val);
                    return;
                }
                let mid = l + (r - l) / 2;
                self.push_down(idx, l, r);
                self._mul(idx << 1, l, mid, tar_l, tar_r, val);
                self._mul(idx << 1 | 1, mid + 1, r, tar_l, tar_r, val);
                self.pull_up(idx);
            }
        }

        impl SegmentTree {
            //public implement
            pub fn new_with_vec_mod(input: Vec<Data>, p: Data) -> SegmentTree {
                let n = input.len();
                let mut ret = SegmentTree {
                    data: vec![
                        SegNode {
                            sum: 0,
                            add_lzy: 0,
                            mul_lzy: 1,
                        };
                        4 * n + 5
                    ],
                    n,
                    p,
                };
                fn build_helper(
                    ret: &mut SegmentTree, input: &Vec<Data>, p: Data, idx: usize, l: usize,
                    r: usize,
                ) {
                    if l == r {
                        ret.data[idx].sum = input[l - 1] % p; //减一减一啊啊啊啊
                        return;
                    }
                    let mid = l + (r - l) / 2;
                    build_helper(ret, input, p, idx << 1, l, mid);
                    build_helper(ret, input, p, idx << 1 | 1, mid + 1, r);
                    ret.pull_up(idx);
                }
                build_helper(&mut ret, &input, p, 1, 1, n);
                ret
            }

            pub fn ask(&mut self, l: usize, r: usize) -> Data {
                self._ask(1, 1, self.n, l, r)
            }

            pub fn add(&mut self, l: usize, r: usize, val: Data) {
                self._add(1, 1, self.n, l, r, val);
            }

            pub fn mul(&mut self, l: usize, r: usize, val: Data) {
                self._mul(1, 1, self.n, l, r, val);
            }
        }
    }

    fn init_reader(file_name: &str) -> Box<dyn BufRead> {
        let read_from: Box<dyn BufRead> = if !file_name.is_empty() {
            let file = std::fs::File::open(std::path::Path::new(file_name))
                .unwrap_or_else(|_| panic!("cannot open {}", file_name));
            // File是一个Read，使用BufReader包装它
            Box::new(BufReader::with_capacity(BUFSIZE, file))
        } else {
            Box::new(BufReader::new(io::stdin()))
        };
        read_from
    }

    fn init() -> (SegmentTree, Vec<Vec<Data>>) {
        let mut reader = init_reader(FILENAME);
        let mut read_u32 = || -> Vec<Data> {
            let mut to_read = String::new();
            reader.read_line(&mut to_read).expect("read arg error");
            to_read
                .split_whitespace()
                .map(|x| x.parse().expect("parse error"))
                .collect()
        };
        let input = read_u32();
        debug_assert_eq!(input.len(), 3);
        let (_, m, p) = (input[0], input[1], input[2]);
        let tmp_data: Vec<Data> = read_u32();
        let tree = SegmentTree::new_with_vec_mod(tmp_data, p);
        let mut to_query: Vec<Vec<Data>> = Vec::with_capacity(m as usize);
        for _ in 0..m {
            to_query.push(read_u32());
        }
        (tree, to_query)
    }

    fn query(tree: &mut SegmentTree, to_query: Vec<Vec<Data>>) {
        let mut writer = BufWriter::with_capacity(BUFSIZE, io::stdout());
        for args in to_query {
            debug_assert!(!args.is_empty());
            match args[0] {
                1 => {
                    debug_assert_eq!(args.len(), 4);
                    tree.mul(args[1] as usize, args[2] as usize, args[3]);
                }
                2 => {
                    debug_assert_eq!(args.len(), 4);
                    tree.add(args[1] as usize, args[2] as usize, args[3]);
                }
                3 => {
                    debug_assert_eq!(args.len(), 3);
                    writeln!(writer, "{}", tree.ask(args[1] as usize, args[2] as usize)).unwrap();
                }
                _ => eprintln!("query option match error!"),
            }
        }
    }

    pub fn run() {
        let (mut tree, to_query) = init();
        query(&mut tree, to_query);
    }
}

fn main() {
    solution::run();
}
