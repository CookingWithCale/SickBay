# [Rapidly manufactured ventilator system specification](https://www.gov.uk/government/publications/coronavirus-covid-19-ventilator-supply-specification/rapidly-manufactured-ventilator-system-specification)

**United Kingdom Department of Health & Social Care**

***Published*** *20 March 2020*

* [Contents](#contents)
* [Ventilation](#ventilation)
* [Gas and electricity](#gas-and-electricity)
* [Infection control](#infection-control)
* [Monitoring and alarms](#monitoring-and-alarm)
* [Miscellaneous](#miscellaneous)
* [Unknown issues](#unknown-issues)

This is a specification of the minimally (and some preferred options) clinically acceptable ventilator to be used in UK hospitals during the current SARS-CoV2 outbreak. It sets out the clinical requirements based on the consensus of what is ‘minimally acceptable’ performance in the opinion of the anaesthesia and intensive care medicine professionals and medical device regulators.

It is for devices, which are most likely to confer therapeutic benefit on a patient suffering with ARDS caused by COVID-19, used in the initial care of patients requiring urgent ventilation. A ventilator with lower specifications than this is likely to provide no clinical benefit and might lead to increased harm, which would be unacceptable for clinicians and would, therefore, not gain regulatory approval.

It must be borne in mind that intensive care medicine is a whole system of care and ventilators cannot be safely used on any patient without trained staff and other equipment and medicines. Where these impinge on the specification they are mentioned below.

It is proposed these ventilators would be for short-term stabilisation for a few hours, but this may be extended up to 1-day use for a patient in extremis as the bare minimum function. Ideally it would also be able to function as a broader function ventilator which could support a patient through a number of days, when more advanced ventilatory support becomes necessary.

## Ventilation

At least 1, optionally 2 modes of ventilation:

* must have mandatory ventilation (for the deeply sedated and paralysed). The user can set a tidal volume and the output is a pressure regulated flow to achieve this volume, for example, pressure regulated volume control (PRVC), SIMV-PC
* optional pressure support mode for those patients breathing to some extent themselves, for example, BIPAP. The user sets an inspiratory pressure and an expiratory pressure. The ventilator can sense when a patient starts to breathe in and apply the inspiratory pressure, then sense when the patient starts to breathe out and apply the expiratory pressure (this pressure is still positive but lower than the inspiratory pressure)
If the patient stops breathing in pressure support mode, it must failsafe automatically onto mandatory ventilation.

Inspiratory airway pressure, the higher pressure setting that is applied to make the patient breathe in:

* plateau pressure should adapt to achieve volume and be limited to 35 cmH2O
* peak pressure should be no more than 2 cmH2O greater than plateau pressure
* ideally there should be a mechanical failsafe valve that opens at 40 cmH2O

Positive End Expiratory Pressure PEEP (usually called EPAP during pressure support mode). The lower pressure applied to the patients airway to allow them to breathe out, but not too much:

* range 5 to 25 cm H2O adjustable in 5 cmH2O increment
* patient breathing system must remain pressurised to at least the PEEP level setting at all times

Inspiratory:Expiratory ratio (I:E) (note, confusingly, it is actually E/I time). The proportion of each breathing cycle that is spent breathing in compared to breathing out:

* 2.0 (i.e. expiration lasts twice as long as inspiration)
* optionally adjustable in the range 1.0 to 3.0

Respiratory Rate. The number of breathing cycles every minute:

* range 10 to 30 breaths per minute in increments of 2 (only in mandatory mode) can be set by the user

Tidal Volume (Vt). The volume of gas flowing into the lungs during one inspiratory cycle:

* must have at least one setting of 400ml +/- 10 ml
* ideally 350ml and 450 ml options
* optionally Range 250 to 600 ml in steps of 50ml
* even more optionally up to 800 ml
* optionally the ability to input body weight and have volume calculated as, for example, 6ml/kg of ideal body weight

## Gas and electricity

Incoming gas supply:

* all gas connectors and hoses must use standard non-interchangeable connectors and be colour coded according to current standards
* must connect to wall pipeline oxygen supply via Schrader valve connector (BS 5682, not the bicycle wheel version). If hose not permanently fixed to machine, then must connect with NIST (Non-Interchangeable Screw Thread – ISO 10802). Oxygen pipeline pressure is 4 to 5 Bar
* optionally can incorporate a backup oxygen cylinder connected via either Schrader valve or Pin Index System
* must be able to be operated on any attached cylinders. Oxygen cylinder pressure is either 1 to 137 bar if no regulator is fitted, or 4 bar if the cylinder incorporates a pressure regulator. The ventilator must be able to work with either. The ventilator must include a pressure regulator to decrease 137 bar cylinder pressure to 4 bar working pressure. Working pressure inside the ventilator may be up to 4 bar, but it must be impossible to expose the patient to any pressure above 40 cmH2O
* optionally can connect to wall pipeline medical air via Schrader valve (NB ‘medical air’ is 4 bar. Must not connect to ‘surgical air 7 bar’ supply)
* optionally can connect to Anaesthetic Gas Scavenging System
* optionally can operate using an oxygen concentrator device for input oxygen

Electricity supply:

* should connect to 240V mains
* battery backup – see below. Must have 20 minutes backup battery in case of mains electricity failure
* optionally hot swappable batteries so that it can be run on battery supply for an extended period, for example, 2 hours for within hospital transfer
* must avoid harmful RF or EM emissions that could interfere with other critical machinery

Gas supply to patient:

* user must be able to control inspired oxygen proportion (FiO2). The percentage of oxygen in the gas being breathed in by the patient. Room air is 21% oxygen
* at least 50% and 100% options
* very preferably ideally variable between 30 and 100% in 10% steps
* patient breathing system connections: the ventilator must present 22mm outside diameter (OD) ‘male’ standard connectors for connection to user supplied 22mm ‘female’ connectors on the breathing system

All elements in the gas pathway must meet biological safety and oxygen safety standards, especially to minimise risk of fire or contamination of the patient’s airway.

## Infection control

All parts coming into contact with the patient’s breath must be either disposable or decontaminatable between patients.

All external surfaces must be cleanable in the likely event that they get respiratory secretions or blood splatter on them. Cleaning would be by healthcare workers manually wiping using an approved surface wipe with disinfectant or cloths and approved surface cleaning liquid.

There will be a separately sourced HMEF-bacterial-viral filter between the machine and patient which may impact on resistance within the system, which may need to be accounted for with some designs. The pressure being delivered to the patient is the specified pressure. If the filter has a resistance of, say 2 cmH2O, the ventilator needs to output 37 cmH2O to achieve a set 35 cmH2O at the patient. This will need further detailed consideration. Usually HMEF filters have negligible resistance, but the viral filtering filters may have much higher resistance that may be clinically relevant.

Optionally include facility for ultrasonic humidifier-warmer to be included.

## Monitoring and alarms

Must alarm at:

* gas or electricity supply failure
* machine switched off while in mandatory ventilation mode
* inspiratory airway pressure exceeded
* inspiratory and PEEP pressure not achieved (equivalent to disconnection alarm)
* tidal volume not achieved or exceeded

### Monitoring

The following should be continuously displayed so the user can verify:

* current settings of tidal volume, frequency, PEEP, FiO2, ventilation mode
* actual achieved rates of tidal volume, breathing rate, PEEP, plateau pressure, FiO2
* if it exists, in pressure support mode there must be real-time confirmation of each patient breath and an alarm if below acceptable range
* optionally CO2 monitoring included

## Miscellaneous

Must be reliable. It must have 100% duty cycle for up to 14 days.

Optionally it can be used beyond 14 days, the expected durability must be specified.

Can be floor standing.

Ideally small and light enough to mount on patient bed and orientation-independent functioning.

Should be as robust as possible. For example, it may be dropped from bed height to floor.

It must be intuitive to use for qualified medical personnel, but these may not be specialists in ventilator use:

must not require more than 30 minutes training for a doctor with some experience of ventilator use
must include instructions for use
ideally instructions for use should be built into the labelling of the ventilator, for example, with ‘connect this to wall’ etc
must include clear labelling of all critical functions and controls using standard terms, pictograms and colours that will be readily recognised by UK healthcare staff
Must have transparent design, supply chain, manufacture and testing processes that are of sufficient quality to enable MHRA officials to deem appropriate for usage in exceptional circumstances.

Must not be excessively cumbersome so that it would impede hospital operations or prevent easy movement within hospital premises.

Must be made from materials and parts readily available in the UK supply chain (anticipating increasing global restrictions on freight movement).

Standards

There are many standards that exist in this area. Below is a list of the most relevant ones. They are not formal regulatory requirements but many are harmonised against regulatory requirements. Consider them as helpful advisory standards for now. MHRA will lead an exercise to define which can be ‘safely’ relaxed for this emergency situation:

BS EN 794-3:1998 +A2:2009: Particular requirements for emergency and transport ventilators
ISO 10651-3:1997: Lung ventilators for medical use – emergency and transport
BS ISO 80601-2-84:2018: Medical electrical equipment. Part 2 to 84. Particular requirements for basic safety and essential performance of emergency and transport ventilators – especially the parts on ‘patient gas pathway’ safety (very similar to IEC 60601)
BS ISO 19223:2019: Lung ventilators and related equipment. Vocabulary and semantics
Unknown issues
How plentiful is 4-bar oxygen supply?

absolute minimum oxygen requirement is the human consumption of about 250 ml/min. However, achieving this is only possible if certain breathing system designs are used and ‘driving’ gas is done by air. Specifically, would have to use circle breathing system with active CO2 absorption
if consumption in the range 1 to 2 l/min is acceptable, then a wider range of designs is possible, but some very basic designs are not
if consumption in the range 10l/min is acceptable, then any possible design can be considered
What is the resistance of HMEF-bacterial-viral filters that are to be used with the ventilator? Is it clinically relevant?

Is there any need to consider running from only low pressure oxygen, for example, from a concentrator? This makes design more complex.

How plentiful is the supply of syringe drivers and drugs for sedation?

if limited, then a vaporiser could be used to vaporise Isoflurane for sedation
this would need certain breathing system designs, mandatory AGSS and a supply of vaporisers
If monitoring can be done by another machine, it could be left out of the ventilator, but essential parameters must be available to the clinician.

Battery backup

Every current ventilator used inside hospitals has a battery backup, so users will expect it to be there and will behave as if it is, for example, unplug it from the wall in order to rearrange cables or while manoeuvring the patient. However, this needs very careful thought to balance the risks. Including this in the spec means instantly trying to source 30,000 large, heavy batteries. Specifying a DC voltage (ie 12VDC) may well be the most sensible for the machine working voltage. Need the advice of an electronic engineer with military/resource limited experience before specifying anything here. It needs to be got right first time.