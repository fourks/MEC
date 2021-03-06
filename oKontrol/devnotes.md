# Development Notes
This document is a mix of 'todos', brain dumps, general ideas on way forward.
it is **not** definitive, things are still in a state of flux.

# Status
pre-alpha, development, code that is untested, and is likely not working - no **not** use.

# TO DO
stuff that is obviously outstanding
- refactor, many things are setup purely for testing concepts

# design
overall design is to allow for a peer to peer parameter system, essentially oKontrol is responsible for 'syncronising' parameters across a transport.

software layers : general -> pure data layer -> organelle layer (?)
general layer:
- parameter data mapping
- osc transmit/recieve of parameters
- file storage - for presets
- map parameter scaled input (0..1, relative) to actual value
- parameter takeover functionality (relates to active page/potentmeter type)
- midi mapping/learn

overall design is to allow for a peer to peer parameter system, essentially oKontrol is responsible for 'syncronising' parameters across a transport.

pure data layer :
- pure data messages
- send pd messages e.g. s r_mix

device layer - organelle :
- screen
- pots
- encoder reception
  
## parameter definitions
currently, we define parameters in PD via messages to the external, however, there are advantages to moving to a parameter file, so the pd patch is only really bound by the usage of the external and the 'receive name'

## midi mapping / learn
allow assignment of parameter to a midi cc
device later could allow learn, e.g. activate learn, twist param, fire cc


## heirarcy for parameters
current implementation is page->params
however, we need to also allow at least for multiple clients 
e.g. 
/device/page/parameter
also do we need to even sub group these? 
e.g. 
/device/module/page/parameter
this might be a bit much? but it would be nice to move to a less rigid heirachy

to stop loops, do we need to allow only the owner to make the change? but if so how do we get fast local feedback?
(currently, we do the change locally, then its overwritten, we are using parameter source)

the issue with forming a heirarchy is parameters are forced to be on one page... rather having arbitary grouping of parameters
the current model, has parameters as a top level entity where, they pages are a container.

however... what we need to do, is to have parameter ids unique for a particular device/patch....



## osc messaging format
move to a message heirarcy 
version osc messages (or clients?)

/host/patch/parameterid
/host/patch/page

example:
/kontrol/param/**organelle/wrpsbrds/o_transpose** "pitch" -24 24 0 
/kontrol/page/**organelle/wrpsbrds/osc** "oscillator" o_transpose 
/kontrol/changed/**organelle/wrpsbrds/o_transpose** 12

note: the highlighted part is unique

shorter names?
/ok/pm/organelle/wrpsbrds/o_transpose pitch  -24 24 0 
/ok/pg/organelle/wrpsbrds/osc "oscillator" o_transpose 
/ok/ch/organelle/wrpsbrds/o_transpose 12

in a modular system, then modules could take the place of patch, or suffixed.
e.g. 
/ok/pm/organelle/modpatch_slot1/o_pitch frequency "base pitch" 0 48000 440 


## json parameter file 
(pseudo only ;) )
[code]
patch : {
    name : wrpsbrds,
    parameters : {
        o_transpose {
            type : pitch, 
            displayname : transpose,
            min : -24,
            max : 24,
            default : 0
        }
        ...
    }, 
    pages : {
        page_1 {
            displayname: oscillator
            parameters : [
                o_transpose, 
            ]
        }
    }
}
[/code]



## json patch file (?)
lets start with (e.g.) 10 presets, which can be saved/recalled
store presets as param name , value
preset {
    0 : {
        o_transpose : 12,
        r_mix : 50
    }
}, 
midi_mapping : {
    cc : {
        63 : o_transpose
    }
}



# pure data messages:


currently we have:
page page1 "reverb"  - adds a page called page1, displayed as reverb

param r_mix page1 pct "mix" 0 100 50 - add parameter r_mix to page 1, displayed as mix, 0 to 100 percent, 50 default
param r_active page1 bool "active" on 
param r_time page1 msec "time"  
param r_feedback page1 pct "feedback" on 

connect port

organelle messages... rawknob1-4 encoder, this is because we can't directly listen to mother host, since mother.pd is blocking us. 
(this could change in teh future if we replace mother.pd)

the idea is to move away from messages, and try to move to using a json configuration file

## notes
types/range change depending on type.


# types
pct     - 54 %  (allow decimals?)
linHz   - 1330 hz (linear hz)
expHz   - 1330 hz (exponential hz)
semis   - 1 sem
octave  - 1 oct
bool    - on/off
second  - 15 s (allow dec?)
msec    - 100 mSec (milliseconds)

advanced types , later on
enum  -  e.g. hall|room|drum 

# display 
need to right justify text, variable space in middle.
page name in bottom right?
Aux function test? (all pages, or per page?)
e.g
```
I ======    O ==========
|mix                45%|
|active              on|
|time         1500 mSec|
|feedback           45%|
Aux = blah      [Reverb]
```

twist encoder, display next/prev page as overlay, only display params on encoder up
```
I ======    O ==========
|mix                45%|
|ac------------------on|
|ti|<  Oscs        >|ec|
|fe------------------5%|
Aux = blah      [Reverb]
```





