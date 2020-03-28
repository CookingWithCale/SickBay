# [SickBay](../../../).[Respiratory](../)

## Ventilator

This folder contains the specifications for creating ventilators but does not contain any module design.

### Variable Formulas

The table bellow lists the four respiratory volumes (determined by spirometry) used to indirectly calculate the respiratory capacity:

| Respiratory volume         | Symbol | Normal | Description |
|:--------------------------:|:------:|:------:|:------------|
| Inspiratory reserve volume |  IRV   |   3L   | The amount of air that can be forcefully inspired after a normal inspiration. |
| Tidal volume               |   TV   |  0.5L  | The volume of air which is circulated through inhalation and expiration during one normal respiration. |
| Expiratory reserve volume  |  ERV   |  1.2L  | The volume of air which can be exhaled forcefully after a normal expiration.           |
| Residual volume            |   RV   |  1.2L  | The amount of air that remains in the lungs after normal expiration. |

The four lung capacities can be calculated using the formulas:

* Vital capacity (VC) = Inspiratory reserve volume (IRV) + Tidal volume (TV) + Expiratory reserve volume (ERV)
* Inspiratory capacity (IC) = Inspiratory reserve volume (IRV) + Tidal volume (TV)
* Functional residual capacity (FRC) = Expiratory reserve volume (ERV) + Residual volume (RV)
* Total lung capacity (TLC) = Inspiratory reserve volume (IRV) + Tidal volume (TV) + Expiratory reserve volume (ERV) + Residual volume (RV)

The following table summarizes the above formulas and introduces the normal values for the four pulmonary capacities, differentiated by gender:

| Lung capacity                      | Formula             | Men (L) | Women (L) |
|:-----------------------------------|:--------------------|:--------|:----------|
| Vital capacity (VC)                | IRV + TV + ERV      | 4.6     | 3.1       |
| Inspiratory capacity (IC)          | IRV + TV            | 3.5     | 2.4       |
| Functional residual capacity (FRC) | ERV + RV            | 2.3     | 1.8       |
| Total lung capacity (TLC)          | IRV + TV + ERV + RV | 5.8     | 4.2       |

### Tidal Volume Calculation

Large Tidal volumes have been associated with increased death rate in patients, possibly going from a rate of 39.8% vs 31.0%). For this reason ideal body weight should be used instead of actual body weight because the lung volume doesn't change with weight gained.

* Male: 50 + (0.91) [height (cm) – 152.4] or 50 + 2.3[height (inches) – 60]
* Female: 45.5 + (0.91) [height (cm) – 152.4] or 45.5 + 2.3[height (inches) – 60]

Maximum tidal volume: 8 ml per kilogram
Maintain end-inspiratory plateau pressure ≤ 30 cm H2O to avoid alveolar overdistention and lowering the targeted tidal volume below 8 ml/kg if that pressure is exceeded.

Set tidal volumes of 6-8 mL/kg ideal body weight seems to fit the right answer for just about
everyone, but there will likely be refinements in the future.

Deliver tidal volumes of no more than 8 mL/kg, holding plateau airway pressures below 30 cmH2O, and including an appropriate PEEP level.

If blood gases can be normalized at the same time, then do so; however, doing so is secondary to the volume and pressure limits.

#### Sources

* [Lung Capacity Calculator](https://www.mdapp.co/lung-capacity-calculator-350/)
* [Setting the Tidal Volume In Adults Receiving Mechanical Ventilation](https://www.nbrc.org/wp-content/uploads/2017/07/Setting-the-Tidal-Volume.pdf)
* [Rapidly manufactured ventilator system specification](./rapidly_manufactured_ventilator_system_spec)

## How to Contribute

The best way to learn how to contribute to SickBay is to read the Quickstart Guide of the Pandemic Cookbook at <https://pandemiccookbook.org/getting_started/quickstart_guide>.

## License

Copyright © 2020 [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
