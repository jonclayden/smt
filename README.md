[![CI](https://github.com/jonclayden/smt/actions/workflows/ci.yaml/badge.svg)](https://github.com/jonclayden/smt/actions/workflows/ci.yaml)

# SMT

The [Spherical Mean Technique (SMT)](http://dx.doi.org/10.1002/mrm.25734) is a clinically feasible method for microscopic diffusion anisotropy imaging. The purpose is to map microscopic features unconfounded by the effects of fibre crossings and orientation dispersion, which are ubiquitous in the brain. This technique requires only an off-the-shelf diffusion sequence with two (or more) b-shells achievable on any standard MRI scanner, thus facilitating its widespread use in neuroscience research and clinical neurology. So far, SMT comes in two flavours, a microscopic tensor model and a simple multi-compartment model. This software was developed and is maintained by [Enrico Kaden](https://ekaden.github.io) from University College London. This fork has some patches by Jon Clayden.

## Installing

Prebuilt SMT binaries are available for 64-bit Linux and macOS systems:
* Download the latest [SMT release](https://github.com/ekaden/smt/releases/latest).
* Unpack the software archive.
* Set the path variable using `export PATH="/path/to/smt/bin:${PATH}"` (in bash) or `setenv PATH "/path/to/smt/bin:${PATH}"` (in csh).

## Building

SMT requires the following software (tested under [Red Hat Enterprise Linux 6](https://www.redhat.com/en/technologies/linux-platforms/enterprise-linux/) and [Apple macOS Mojave 10.14](https://www.apple.com/macos/)):
* [git](https://git-scm.com/) (version 1.9 or later)
* [cmake](https://cmake.org/) (version 2.8 or later)
* [GNU C/C++ compiler](https://gcc.gnu.org/) (version 4.9 or later), [Clang C/C++ compiler](http://clang.llvm.org/) (version 3.5 or later) or [Intel C/C++ compiler](https://software.intel.com/en-us/c-compilers/) (version 16.0 or later)

Clone the forked SMT repository:
```bash
git clone https://github.com/jonclayden/smt.git
```

Build the software:
```bash
mkdir smt-build
cd smt-build
cmake ../smt
make
```

If necessary, the C/C++ compiler can be set explicitly, for example:
```bash
cmake ../smt -DCMAKE_C_COMPILER=gcc-4.9 -DCMAKE_CXX_COMPILER=g++-4.9
make
```

The SMT programs are located in the build directory.

## Gaussian noise estimation

This utility software provides a voxelwise estimate of the Gaussian-distributed noise from, for example, a set of zero b-value images.

### Usage

```
gaussianfit [options] <input> <output>
gaussianfit (-h | --help)
gaussianfit --license
gaussianfit --version
```

* `<input>` –– Input data set in NIfTI-1 format

* `<output>` –– Output parameter maps in NIfTI-1 format, including:
  1. Mean parameter (`mean`)
  2. Standard deviation parameter (`std`)

If the output name contains a placeholder `{}` (e.g. `output_{}.nii`), the parameter maps are written to separate files using the suffices given in parentheses. Otherwise the output parameter maps are stored in a single file.

### Options

* `--mask <mask>` –– Foreground mask [default: none]. Values greater than zero are considered as foreground.

* `-h, --help` –– Help screen

* `--license` –– License information

* `--version` –– Software version

### Environment variables

* `SMT_DEBUG=<true | positive integer` –– Debug information

* `SMT_NOCOLOUR=<true | positive integer` or `SMT_NOCOLOR=<true | positive integer` –– Suppress colour output

* `SMT_NUM_THREADS=<positive integer>` –– Number of threads for parallel processing

* `SMT_QUIET=<true | positive integer>` –– Verbosity (e.g. progress bar)

## Rician noise estimation

This utility software provides a voxelwise estimate of the Rician-distributed noise from, for example, a set of zero b-value images.

### Usage

```
ricianfit [options] <input> <output>
ricianfit (-h | --help)
ricianfit --license
ricianfit --version
```

* `<input>` –– Input data set in NIfTI-1 format

* `<output>` –– Output parameter maps in NIfTI-1 format, including:
  1. Location parameter (`loc`)
  2. Scale parameter (`scale`)

If the output name contains a placeholder `{}` (e.g. `output_{}.nii`), the parameter maps are written to separate files using the suffices given in parentheses. Otherwise the output parameter maps are stored in a single file.

### Options

* `--mask <mask>` –– Foreground mask [default: none]. Values greater than zero are considered as foreground.

* `-h, --help` –– Help screen

* `--license` –– License information

* `--version` –– Software version

### Environment variables

* `SMT_DEBUG=<true | positive integer` –– Debug information

* `SMT_NOCOLOUR=<true | positive integer` or `SMT_NOCOLOR=<true | positive integer` –– Suppress colour output

* `SMT_NUM_THREADS=<positive integer>` –– Number of threads for parallel processing

* `SMT_QUIET=<true | positive integer>` –– Verbosity (e.g. progress bar)

## Microscopic diffusion tensor

This microscopic model estimates the microscopic fractional anisotropy and other microscopic diffusion coefficients in tissue with complex directional architecture as in the brain.

### Usage

```
fitmicrodt [options] <input> <output>
fitmicrodt (-h | --help)
fitmicrodt --licence
fitmicrodt --version
```

* `<input>` –– Input diffusion data set in NIfTI-1 format

* `<output>` –– Output parameter maps in NIfTI-1 format, including:
  1. Longitudinal microscopic diffusivity (`long`)
  2. Transverse microscopic diffusivity (`trans`)
  3. Microscopic fractional anisotropy (`fa`)
  4. Microscopic fractional anisotropy to the third power (`fapow3`)
  5. Microscopic mean diffusivity (`md`)
  6. Zero b-value image (`b0`)

If the output name contains a placeholder `{}` (e.g. `output_{}.nii`), the parameter maps are written to separate files using the suffices given in parentheses. Otherwise the output parameter maps are stored in a single file.

### Options

* `--bvals <bvals>` –– Diffusion weighting factors (s/mm²), given in FSL format

* `--bvecs <bvecs>` –– Diffusion gradient directions, given in FSL format

* `--grads <grads>` –– Diffusion gradients (s/mm²), given in MRtrix format

* `--graddev <graddev>` –– Diffusion gradient deviation [default: none], provided as NIfTI-1 tensor volume

* `--mask <mask>` –– Foreground mask [default: none]. Values greater than zero are considered as foreground.

* `--rician <rician>` –– Rician noise [default: none]. SMT assumes Gaussian noise by default. Alternatively, a Rician noise model may be chosen, in which case the signal measurements are [adjusted](http://dx.doi.org/10.1002/mrm.25734) to reduce the Rician-noise induced bias. The noise level can be specified either globally using a scalar value or voxel by voxel using a NIfTI-1 image volume.

* `--maxdiff <maxdiff>` –– Maximum diffusivity (mm²/s) [default: 3.05e-3]. Typically the self/free-diffusion coefficient for a certain temperature is chosen.

* `--b0` –– Model-based estimation of the zero b-value signal. By default, the zero b-value signal is estimated as the mean over the measurements with zero b-value. If this option is set, the zero b-value signal is fitted using the microscopic diffusion model. This is also the default behaviour when measurements with zero b-value are not provided.

* `-h, --help` –– Help screen

* `--license` –– License information

* `--version` –– Software version

### Environment variables

* `SMT_DEBUG=<true | positive integer` –– Debug information

* `SMT_NOCOLOUR=<true | positive integer` or `SMT_NOCOLOR=<true | positive integer` –– Suppress colour output

* `SMT_NUM_THREADS=<positive integer>` –– Number of threads for parallel processing

* `SMT_QUIET=<true | positive integer>` –– Verbosity (e.g. progress bar)

## Multi-compartment microscopic diffusion

This model provides estimates of microscopic features specific to the intra- and extra-neurite compartments unconfounded by the effects of the potentially complex fibre orientation distribution.

### Usage

```
fitmcmicro [options] <input> <output>
fitmcmicro (-h | --help)
fitmcmicro --licence
fitmcmicro --version
```

* `<input>` –– Input diffusion data set in NIfTI-1 format

* `<output>` –– Output parameter maps in NIfTI-1 format, including:
  1. Intra-neurite volume fraction (`intra`)
  2. Intrinsic diffusivity (`diff`)
  3. Extra-neurite transverse microscopic diffusivity (`extratrans`)
  4. Extra-neurite microscopic mean diffusivity (`extramd`)
  5. Zero b-value image (`b0`)

If the output name contains a placeholder `{}` (e.g. `output_{}.nii`), the parameter maps are written to separate files using the suffices given in parentheses. Otherwise the output parameter maps are stored in a single file.

### Options

* `--bvals <bvals>` –– Diffusion weighting factors (s/mm²), given in FSL format

* `--bvecs <bvecs>` –– Diffusion gradient directions, given in FSL format

* `--grads <grads>` –– Diffusion gradients (s/mm²), given in MRtrix format

* `--graddev <graddev>` –– Diffusion gradient deviation [default: none], provided as NIfTI-1 tensor volume

* `--mask <mask>` –– Foreground mask [default: none]. Values greater than zero are considered as foreground.

* `--rician <rician>` –– Rician noise [default: none]. SMT assumes Gaussian noise by default. Alternatively, a Rician noise model may be chosen, in which case the signal measurements are [adjusted](http://dx.doi.org/10.1002/mrm.25734) to reduce the Rician-noise induced bias. The noise level can be specified either globally using a scalar value or voxel by voxel using a NIfTI-1 image volume.

* `--maxdiff <maxdiff>` –– Maximum diffusivity (mm²/s) [default: 3.05e-3]. Typically the self/free-diffusion coefficient for a certain temperature is chosen.

* `--b0` –– Model-based estimation of the zero b-value signal. By default, the zero b-value signal is estimated as the mean over the measurements with zero b-value. If this option is set, the zero b-value signal is fitted using the microscopic diffusion model. This is also the default behaviour when measurements with zero b-value are not provided.

* `-h, --help` –– Help screen

* `--license` –– License information

* `--version` –– Software version

### Environment variables

* `SMT_DEBUG=<true | positive integer` –– Debug information

* `SMT_NOCOLOUR=<true | positive integer` or `SMT_NOCOLOR=<true | positive integer` –– Suppress colour output

* `SMT_NUM_THREADS=<positive integer>` –– Number of threads for parallel processing

* `SMT_QUIET=<true | positive integer>` –– Verbosity (e.g. progress bar)

## Citation

If you use this software, please cite:

* General Spherical Mean Technique (SMT)

Kaden E, Kruggel F, and Alexander DC: Quantitative Mapping of the Per-Axon Diffusion Coefficients in Brain White Matter. Magnetic Resonance in Medicine, vol. 75, pp. 1752–1763, 2016. DOI: [10.1002/mrm.25734](http://dx.doi.org/10.1002/mrm.25734)
<!-- Bibtex entry? -->

* Microscopic diffusion tensor model

Kaden E, Kruggel F, and Alexander DC: Quantitative Mapping of the Per-Axon Diffusion Coefficients in Brain White Matter. Magnetic Resonance in Medicine, vol. 75, pp. 1752–1763, 2016. DOI: [10.1002/mrm.25734](http://dx.doi.org/10.1002/mrm.25734)
<!-- Bibtex entry? -->

* Multi-compartment microscopic diffusion model

Kaden E, Kelm ND, Carson RP, Does MD, and Alexander DC: Multi-compartment microscopic diffusion imaging. NeuroImage, vol. 139, pp. 346–359, 2016. DOI: [10.1016/j.neuroimage.2016.06.002](http://dx.doi.org/10.1016/j.neuroimage.2016.06.002)
<!-- Bibtex entry? -->

## Supplementary material

* [ISMRM 2016 slides](docs/pdf/KadenISMRM2016.pdf)
* [OHBM 2016 poster](docs/pdf/KadenOHBM2016.pdf)

## License

SMT is released under the [BSD Two-Clause License](LICENSE.md). This software is based on or incorporates materials from [third-party projects](THIRDPARTY.md).
