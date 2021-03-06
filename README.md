# Robot Simulator

This project is a sandbox for designing control systems focused on 2 wheeled agent dynamics.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The automatic provisioning script was tested on an Intel® Core™ i7 machine running the Debian 9 Linux distribution. By now, there is no need for GPUs or any kind of additional computing device.

* [Debian 9](https://www.debian.org/index.html) - The Linux distro used;
* [Git](https://git-scm.com/doc) - The version control system used.

### Installing

The following instructions were tailored to OSes with Debian-like package management system.

Update installed packages (requires root password):
```
sudo apt update -y
sudo apt upgrade -y
```

Get the sources:
```
cd /your/prefered/working/directory/
git clone https://github.com/LBBassani/Robot-Simulator.git
```
Compile the project:
```
make
```

To run example simulation, run:

```
./bin/erusvsssim
```
A new window will open up like this:

![Simulator Window](/images/player_on_field.png?raw=true "Title")


## Authors

* **Thaylo Freitas** - *Initial work* - [Thaylo](https://github.com/thaylo)

See also the list of [contributors](https://github.com/Thaylo/Robot-Simulator/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* UFES Robotics Team (former and current members)
* UFES Computer Engineering PET (Tutorial Education Program)
* UFES Department of Informatics (professors)
