# Taggleos

A fun project to make a tag based storage API in C++ to help me learn more about
C++.

I let Claude Sonnet 4 implement this project from just the readme you see here.
I followed along but 100% of the code, files, etc... in this directory excluding this readme
were written by that AI.

Minus the installation of Qt6 library, it was able to build and run the application after one or two compilation debugging sessions.

## Core Design Notes

// Core Concepts

  Result<Type> { Type | Problem | Error }

  DataID { UUID }

  TagID { UUID? }
  
  Tag { TagID, Name, Parent<Tag>, Children<Tag>[] } // Strictly heirarchical structure?

  ExpirmentalTag { Name, Parents<tag>[], Children<tag>[], Siblings<tag[]>} // Directional graph?

  SuperExperimentalTag { Name, Related<tag>[]} // Generic Graph??

  Data { bytes }

// Core APIs

  Save(data, tags[]) -> Result<bool>

  Search(tags[]) -> Result<{id, tags}[]>

  Load(id) -> Result<data>

  Stats() -> Result<todo>

  AddTag(tag) -> Result<id>

  Delete(tag) -> Result<{bool, DataID[]}>

// Core Tags

  tag:id

## Extended Design Notes

### History

  History(id) -> Result<historyRecords[]>

  History(tag) -> Result<historyRecords[]>

### Resilency

// TODO:

Store on redundant devices/services

Store retrievable data history (versions)

Configurable settings

### Performance

// TODO

Store on faster storage

Cache on faster storage

### Secure

// TODO

Encryption

Access Controls

### Expiration

// TODO

Automatic Deletion After T time

Automatic Archival After T time

### Archival

// TODO

Compression

Move to less important storage device/service
