type canvas;
type context;
type event;

external getClientX : event => float = "clientX" [@@bs.get];
external getClientY : event => float = "clientY" [@@bs.get];

external getElementById : string => canvas = "document.getElementById" [@@bs.val];
external width : canvas => int = "width" [@@bs.get];
external height : canvas => int = "height" [@@bs.get];  
external addEventListener : canvas => string => (event => unit) => unit = "" [@@bs.send];

external getContext : canvas => string => context = "" [@@bs.send];
let getContext2d id => getContext (getElementById id) "2d";
external moveTo : context => float => float => unit = "" [@@bs.send]; 
external lineTo : context => float => float => unit = "" [@@bs.send];
external beginPath : context => unit = "" [@@bs.send];
external stroke : context => unit = "" [@@bs.send];
external fill : context => unit = "" [@@bs.send];
external fillStyle : context => string => unit = "" [@@bs.set];
external clearRect : context => int => int => int => int => unit = "" [@@bs.send];
external arc : context => float => float => float => float => float => bool => unit = "arc" [@@bs.send];


let drawLine context x1 y1 x2 y2 => {
    beginPath context;
    moveTo context x1 y1;
    lineTo context x2 y2;
    stroke context;
};

let drawVector context (px, py) (vx, vy) => {
    drawLine context px py (px +. vx) (py +. vy)
};

let colour2str (colour: Colour.t) => {
    switch colour {
        | RGB r g b => {j|rgb($(r), $(g), $(b)|j}
        | RGBA r g b a => {j|rgba($(r), $(g), $(b), $(a))|j}
    };
};

let drawCircle ::colour=(0,0,0) context (x, y) radius => {
    beginPath context;
    let (r, g, b) = colour;
    fillStyle context {j|rgb($(r), $(g), $(b))|j};
    arc context x y radius 0. (2. *. Math.pi) false;
    fill context;
};

let canvas = getElementById "canvas";
let clearCanvas context => {
    clearRect context 0 0 (width canvas) (height canvas);
};