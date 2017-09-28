type t = (float, float);

let zero = (0.0, 0.0);
let down = (0.0, 1.0);

external pi : float = "Math.PI" [@@bs.val];

let add (x1, y1) (x2, y2) => {
  (x1 +. x2, y1 +. y2)
};

let sub (x1, y1) (x2, y2) => {
  (x1 -. x2, y1 -. y2)
};

let invert (x, y) => (-.x, -.y);

let mul (x, y) scalar => (x *. scalar, y *. scalar);
let angle2unitVector angle => ((sin (angle *. 2.0 *. pi)), (cos (angle *. 2.0 *. pi)));

let div (x, y) scalar => (x /. scalar, y /. scalar);
let length (x, y) => sqrt (x *. x +. y *. y);
let length2 (x, y) => (x *. x +. y *. y);
let normalise vector => {
  let l = length vector;
  div vector l;
};

let vector2angle vector => {
  let (x, y) = normalise vector;
  atan2 y x
};

Random.init 20;
let randomUnit () => {
  Random.float (2. *. pi) |> angle2unitVector;
}