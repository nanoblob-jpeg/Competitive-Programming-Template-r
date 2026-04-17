open Printf

module Vector : sig
    type 'a t = {
        mutable size : int;
        mutable capacity : int;
        mutable _arr : 'a option array;
    }
    val size : 'a t -> int
    val capacity : 'a t -> int
    val resize : 'a t -> int -> unit
    val push_back : 'a t -> 'a -> unit
    val back : 'a t -> 'a
    val front : 'a t -> 'a
    val get : 'a t -> int -> 'a
    val ( .%() ) : 'a t -> int -> 'a
    val set : 'a t -> int -> 'a -> unit
    val ( .%()<- ) : 'a t -> int -> 'a -> unit
    val iter : 'a t -> ('a -> unit) -> unit
    val print : 'a t -> ('a -> unit) -> unit
    val make : ?size:int -> 'a -> 'a t
    val init : ?size:int -> (int -> 'a) -> 'a t
    val bsearch : 'a t -> 'b -> ?l:int -> ?r:int -> ('a -> 'b -> int -> bool) -> int
    val lower_bound : 'a t -> ?l:int -> ?r:int -> ('b -> 'a -> int -> int) -> 'b -> int
    val upper_bound : 'a t -> ?l:int -> ?r:int -> ('b -> 'a -> int -> int) -> 'b -> int
end = struct
    type 'a t = {
        mutable size : int;
        mutable capacity : int;
        mutable _arr : 'a option array;
    }

    let size v = v.size
    let capacity v = v.capacity
    let _realloc v si =
        assert (si > 0);
        if si > v.capacity then begin
            let new_arr = Array.make si None in
            for i = 0 to (v.size - 1) do
                new_arr.(i) <- v._arr.(i)
            done;
            v._arr <- new_arr;
            v.capacity <- si
        end
    let resize v si = 
        assert (si > 0);
        _realloc v si;
        v.size <- si
    let push_back v add = 
        if v.size = v.capacity then begin
            _realloc v (max 1 (v.size*2))
        end;
        v._arr.(v.size) <- Some add;
        v.size <- (v.size+1)
    let get v index = Option.get v._arr.(index)
    let ( .%() ) v index = get v index
    let set v index add = v._arr.(index) <- Some add
    let ( .%()<- ) v index add = set v index add
    let back v = get v (v.size - 1)
    let front v = get v 0
    let iter v f =
        for i = 0 to (v.size - 1) do
            f (Option.get v._arr.(i));
        done
    let print v f = 
        iter v (fun el -> f el; print_char ' ');
        print_char '\n'

    let make ?(size=0) default =
        let f = (fun _ -> Some default) in
        {size = size; 
        capacity = size; 
        _arr = Array.init size f}

    let init ?(size=0) f = 
        let g = (fun i -> Some (f i)) in
        {size = size; 
        capacity = size; 
        _arr = Array.init size g}


    (* read comments at other definition of this for details. same api *)
    let rec bsearch arr v ?l ?r cond =
        let boundl = Option.value l ~default:0 and
            boundr = Option.value r ~default:(size arr) in
        if boundl >= boundr then boundr
        else 
            begin
                let mid = boundl + (boundr - boundl)/2 in
                if cond (get arr mid) v mid then bsearch arr v ~l:(mid+1) ~r:boundr cond 
                else bsearch arr v ~l:boundl ~r:mid cond 
            end
    let lower_bound arr ?l ?r cond v = bsearch arr v ?l ?r (fun y x i -> (cond x y i) < 0) 
    let upper_bound arr ?l ?r cond v = bsearch arr v ?l ?r (fun y x i -> (cond x y i) <= 0) 
end
let ( .%() ) = Vector.( .%() )
let ( .%()<- ) = Vector.( .%()<- )

let readn amt = List.take amt (List.map int_of_string (String.split_on_char ' ' (read_line ())))
let print_int_array a =
    Array.iter (fun x -> printf "%d " x) a;
    print_newline ()
let print_int_list a = 
    List.iter (fun x -> printf "%d " x) a;
    print_newline ()

type 'a looper = 
    | Next
    | Continue
    | Break
    | Res of 'a
let rec loop_helper l r f incr cond = 
    if cond l r then 
        match f l with
        | Next | Continue -> loop_helper (incr l) r f incr cond
        | Break -> None
        | Res res -> Some res
    else None
let loop ?(incr=fun l -> l+1) ?(cond=fun x y -> x < y) l r f = 
    loop_helper l r (fun x -> f x; Next) incr cond 
let loop_res ?(incr=fun l -> l+1) ?(cond=fun x y -> x < y) l r f = 
    loop_helper l r f incr cond
let rec loop_reduce ?(incr=fun l -> l+1) ?(cond=fun x y -> x < y) l r acc f =
    if cond l r then
        match f acc l with
        | (Next, next_acc) | (Continue, next_acc) -> loop_reduce ~incr ~cond (incr l) r next_acc f
        | (Break,  next_acc) -> next_acc
        | _ -> failwith "f returned invalid"
    else acc
let rep (l, r) f = loop l r f |> ignore
let irep (r, l) f = loop r l f ~incr:(fun l -> l-1) ~cond:(fun x y -> x > y) |> ignore

(* takes a unary comparison op like y < x [mid] and returns first 
    index such that x >= y 
    That is, the function should return true if arr value is ordered before
    search value

    if there is no such index, it returns n, the length of the list
    cond takes (arr value) (search value) (arr index)*)
let rec bsearch arr v ?l ?r cond =
    let boundl = Option.value l ~default:0 and
        boundr = Option.value r ~default:(Array.length arr) in
    if boundl >= boundr then boundr
    else 
        begin
            let mid = boundl + (boundr - boundl)/2 in
            if cond arr.(mid) v mid then bsearch arr v ~l:(mid+1) ~r:boundr cond 
            else bsearch arr v ~l:boundl ~r:mid cond 
        end
(* takes ternary operator for v ? array value, -1 is <; 0 is =; 1 is > 
    cond takes (search value) (arr value) (arr index)*)
let lower_bound arr ?l ?r ?(cond=fun x y _ -> x - y) v = bsearch arr v ?l ?r (fun y x i -> (cond x y i) < 0) 
let upper_bound arr ?l ?r ?(cond=fun x y _ -> x - y) v = bsearch arr v ?l ?r (fun y x i -> (cond x y i) <= 0) 


let solve () = ()

let rec main = function
    | 0 -> ()
    | n -> solve (); main (n-1)
let tc = int_of_string @@ read_line ()
let () = main tc
