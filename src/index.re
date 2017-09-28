let context = Canvas.getContext2d "canvas";
let width = 1900.0;
let height = 1060.0;

let gravity = Vector2.mul Vector2.down 0.0092;
let theOG = (width /. 2.0, height /. 2.0);

module Particle = {
    type t = {
        position: Vector2.t,
        velocity: Vector2.t,
        colour: (int, int, int)
    };

    let make position velocity colour => {
        { position, velocity, colour };
    };

    let draw { position, colour } => {
        Canvas.drawCircle ::colour context position 3.0
    };

    let update { position, velocity, colour } => {
        let v = Vector2.add velocity gravity;
        let p = Vector2.add position v;
        { position: p, velocity: v, colour }
    };
};

let particle = Particle.make theOG (10.0, 0.0);

let state = ref [];
 
type message = 
  | Tick
  | SpawnParticle Vector2.t;

let update state message => {
    switch message {
        | Tick => {
            List.map Particle.update state;
        }
        | SpawnParticle pos => {
            let colour = (Random.int 256, Random.int 256, Random.int 256);
            [Particle.make pos (Vector2.randomUnit ()) colour, ...state];
        };
    };
};

let render state => {
    /* Canvas.clearCanvas context; */
    List.iter Particle.draw state;
};

let dispatch message => {
    state := update !state message;
    render !state;
};

external setInterval : (unit => unit) => int => unit = "setInterval" [@@bs.val];

setInterval (fun () => dispatch Tick) 17;
setInterval (fun () => dispatch (SpawnParticle theOG)) 20;