type element;
type canvas;
type context;
type event;

external parentNode : canvas => element = "parentNode" [@@bs.get];
external clientWidth : element => int = "clientWidth" [@@bs.get];
external clientHeight : element => int = "clientHeight" [@@bs.get];

external getCanvasById : string => canvas = "document.getElementById" [@@bs.val];
external windowInnerWidth : int = "window.innerWidth" [@@bs.val];
external windowInnerHeight : int = "window.innerHeight" [@@bs.val];

external getWidth : canvas => int = "width" [@@bs.get];
external getHeight : canvas => int = "height" [@@bs.get];  
external setWidth : canvas => int => unit = "width" [@@bs.set];
external setHeight : canvas => int => unit = "height" [@@bs.set];  

external addEventListener : canvas => string => (event => unit) => unit = "" [@@bs.send];
external _getContext : canvas => string => context = "getContext" [@@bs.send];

let pi : float = [%bs.raw "Math.PI"];

let getContext canvas contextType => {
    switch contextType {
        | `twoD => _getContext canvas "2d"
        | `threeD => _getContext canvas "3d"
    };
};

external moveTo : context => float => float => unit = "" [@@bs.send]; 
external lineTo : context => float => float => unit = "" [@@bs.send];
external beginPath : context => unit = "" [@@bs.send];
external stroke : context => unit = "" [@@bs.send];
external fill : context => unit = "" [@@bs.send];
external fillStyle : context => string => unit = "" [@@bs.set];
external clearRect : context => int => int => int => int => unit = "" [@@bs.send];
external arc : context => float => float => float => float => float => bool => unit = "arc" [@@bs.send];
external strokeText : context => string => float => float => unit = "strokeText" [@@bs.send];


let drawLine context x1 y1 x2 y2 => {
    beginPath context;
    moveTo context x1 y1;
    lineTo context x2 y2;
    stroke context;
};

let drawVector context origin vector => {
    let (x1, y1) = origin;
    let (x2, y2) = Vector2.add origin vector;
    drawLine context x1 y1 x2 y2;
};

let drawCircle context ::colour=(0,0,0) ::alpha=1.0 center::(x, y) radius => {
    beginPath context;
    let (r, g, b) = colour;
    fillStyle context {j|rgba($(r), $(g), $(b), $(alpha))|j};
    arc context x y radius 0. (2. *. pi) false;
    fill context;
};

let clearCanvas canvas context => {
    clearRect context 0 0 (getWidth canvas) (getHeight canvas);
};
