% OuiSync
% eQualitie
% September 2020

# Introduction

The OuiSync project aims to provide users with a friendly tool to synchronize folders with files between their own devices or those of other users (either trusted or untrusted), while keeping the data private and secure both in transit and in rest, and all that in spite of poor or spotty connectivity between devices and without the need of dedicated servers or even local network infrastructure.

OuiSync implements a distributed protocol for the exchange and synchronization of file changes that allows it to use automatic merge strategies and simple conflict resolution propagation, thus sparing users from manual  or low-level handling of synchronization issues.

OuiSync uses strong encryption when communicating with other devices to protect from eavesdropping and tampering; data is also only propagated to devices selected for storage to enhance privacy, and then only an allowed subset can access the actual files and metadata. When storing data permanently, OuiSync also uses strong encryption that protects it in case of device seizure.

Communications between devices in OuiSync are resistant to interference thanks to technologies developed for the [Ouinet][] project. Peer-to-peer (P2P) techniques are used for the discovery of other devices and communication with them without the need of a server. Local discovery allows devices to talk directly over a (maybe isolated) local network. If no network is available at all, Wi-Fi Direct or Bluetooth can be used instead for direct device-to-device (D2D) communication.

[Ouinet]: https://github.com/equalitie/ouinet/

# Requirements

OuiSync caters to users who want to keep, for availability or backup purposes, copies of a set of files synchronized between different devices be them their own, or belonging to other users.

Also, some of these devices are trusted to access, modify and share file data (like an encrypted smartphone or desktop computer), while others (like a permanently online Raspberry Pi or virtual private server) are only trusted to blindly store and convey data to others.

Moreover, users want the system to behave in a way which is respectful with their privacy, secure, and available despite limited network connectivity.

The previous requirements are in contrast with the majority of existing solutions, where some of the following issues arise:

  - Users rely on third-party providers running servers which can access file data and become a bottleneck and single point of failure or control of the system.
  - Other devices need good network reachability (e.g. static IP address, port-forwarding router) or have to resort to dedicated rendez-vous or tunneling helper servers.
  - Devices need an active network connection even if they are physically close to each other.
  - All devices keeping copies of the data have access to their content.
  - Users need to adopt ad hoc workarounds (like encrypted file system layers or archive files), which break the usability of the system, to keep data private.
  - Conflicting modifications are handled in a user-unfriendly way (if supported at all).
  - Services, protocols and tools are proprietary or closed source, thus an inherent security liability.

# Content

Content.