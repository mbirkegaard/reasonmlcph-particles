type t = (float, float);

let zero = (0.0, 0.0);
let up = (0.0, -1.0);
let down = (0.0, 1.0);
let left = (-1.0, 0.0);
let right = (1.0, 0.0);

external pi : float = "Math.PI" [@@bs.val];

let add (x1, y1) (x2, y2) => {
  (x1 +. x2, y1 +. y2)
};

let sub (x1, y1) (x2, y2) => {
  (x1 -. x2, y1 -. y2)
};

let invert (x, y) => (-.x, -.y);

let mul (x, y) scalar => (x *. scalar, y *. scalar);

let unitVector radians => (sin radians, cos radians);

let div (x, y) scalar => (x /. scalar, y /. scalar);

let length (x, y) => sqrt (x *. x +. y *. y);

let length2 (x, y) => (x *. x +. y *. y);

let normalise vector => {
  let l = length vector;
  div vector l;
};

let vector2radians vector => {
  let (x, y) = normalise vector;
  atan2 y x
};

let randomUnit ::first=0.0 ::second=(2. *. pi) () => {
  let diff = second -. first;
  (first +. Random.float diff) |> unitVector;
};