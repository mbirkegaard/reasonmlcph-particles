let canvas = Canvas.getCanvasById "canvas";
let canvasParent = Canvas.parentNode canvas;
Canvas.setWidth canvas (Canvas.clientWidth canvasParent);
Canvas.setHeight canvas (Canvas.clientHeight canvasParent);
let context = Canvas.getContext canvas `twoD;
let width = float_of_int @@ Canvas.getWidth canvas;
let height = float_of_int @@ Canvas.getHeight canvas;
let center = (width /. 2., height /. 2.);

let gravity = Vector2.mul Vector2.down 0.015;

module Particle = {
    type t = {
        position: Vector2.t,
        velocity: Vector2.t,
        colour: (int, int, int)
    };

    let make position velocity colour => {
        { position, velocity, colour };
    };

    let draw context { position, colour } => {
        Canvas.drawCircle context colour::colour center::position 5.0;
    };

    let update { position, velocity, colour } => {
        let newVelocity = Vector2.add velocity gravity;
        { position: Vector2.add position newVelocity, velocity: newVelocity, colour }
    };
};

type state = list Particle.t;

let state : ref state = ref [];

type msg = 
  | Tick
  | SpawnParticle Vector2.t Vector2.t;

let update msg state => {
    switch msg {
        | Tick => List.map Particle.update state
        | SpawnParticle pos vel => {
            let colour = (Random.int 256,Random.int 256, Random.int 256);
            [Particle.make pos vel colour, ...state]
        }
    };
};

let draw state => {
    Canvas.clearCanvas canvas context;
    List.iter (Particle.draw context) state;
};

let dispatch msg => {
    let newState = update msg !state;
    state := newState;
    draw !state;
};

external setInterval : (unit => unit) => int => unit = "setInterval" [@@bs.val];

setInterval (fun () => dispatch Tick) 10;
setInterval (fun () => dispatch (SpawnParticle center (Vector2.randomUnit ()))) 100;