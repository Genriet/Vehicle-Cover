# Vehicle Cover — Camouflage Your Vehicles

A DayZ mod that lets players camouflage vehicles with camonets without despawning or replacing the original vehicles.

Unlike mods that replace vehicles with covered variants, Vehicle Cover preserves the existing vehicle, allowing it to remain in the world in its original state. Depending on the configuration, players can even drive with the cover attached.

## Features

- **Vehicle camouflage:** Attach camonets to supported vehicles through an in-game action.
- **Vehicle preservation:** Keeps the original vehicle rather than despawning it.
- **Configurable vehicle support:** Define supported vehicle classes and their corresponding cover models.
- **Shape-changing attachments:** Support alternative cover shapes when specified vehicle attachments are present, including attachment-dependent configurations such as tents.
- **Movement-based cover removal:** Optionally drop the cover when a vehicle moves above a configurable speed threshold.
- **Vehicle interaction restrictions:** Configure whether players can enter vehicles, open doors, or modify attachments while a cover is attached.

## Showcase

### Vehicle Cover

[![Watch Vehicle Cover showcase](https://img.youtube.com/vi/5BAOxFKq_DQ/hqdefault.jpg)](https://youtu.be/5BAOxFKq_DQ)

### Custom Cover Tutorial

[![Watch the custom cover tutorial](https://img.youtube.com/vi/VuHL8M8Xl2U/hqdefault.jpg)](https://youtu.be/VuHL8M8Xl2U)

## Configuration

Vehicle Cover uses JSON configuration to define supported vehicles and their behavior.

Example configuration:

```json
{
  "Vehicles": [
    {
      "VehicleClassname": "CivilianSedan",
      "CamonetClassname": "VehicleCover_CivilianSedan",
      "DoorSlotsToCheck": [
        "CivSedanDriverDoors",
        "CivSedanCoDriverDoors",
        "CivSedanCargo1Doors",
        "CivSedanCargo2Doors",
        "CivSedanTrunk",
        "CivSedanHood"
      ],
      "CamonetShapeableSlot": "",
      "CamonetShapeableClassname": "",
      "DropCamonet": 1,
      "SpeedToDrop": 10.0,
      "BlockGettingInWithCamonet": 1,
      "BlockDoorsWithCamonet": 1,
      "BlockAttachmentsWithCamonet": 1,
      "ShouldDoorsBeClosedToAttach": 1
    }
  ]
}
```

### Configuration options

| Option | Description |
|---|---|
| `VehicleClassname` | Vehicle class to support; can also refer to a color-base class. |
| `CamonetClassname` | Class name of the vehicle's cover model. |
| `DoorSlotsToCheck` | Door slots checked when closed doors are required. |
| `CamonetShapeableSlot` | Attachment slot that changes the cover's shape. |
| `CamonetShapeableClassname` | Alternative cover model for the attachment-dependent shape. |
| `DropCamonet` | Enables dropping the cover when the vehicle exceeds the configured speed threshold. |
| `SpeedToDrop` | Vehicle speed threshold for dropping the cover. |
| `BlockGettingInWithCamonet` | Prevents entering a covered vehicle. |
| `BlockDoorsWithCamonet` | Prevents opening doors while the cover is attached. |
| `BlockAttachmentsWithCamonet` | Prevents adding or removing attachments while covered. |
| `ShouldDoorsBeClosedToAttach` | Requires configured doors to be closed before attaching a cover. |

Options marked as unsupported on boats should not be assumed to work for boats.

## For Modders

Vehicle Cover supports configuration for custom vehicles and cover models.

- **Workshop:** [Vehicle Cover](https://steamcommunity.com/sharedfiles/filedetails/?id=3442752056)
- **Custom cover tutorial:** [Watch the tutorial](https://youtu.be/VuHL8M8Xl2U)
- **Model compatibility:** Models originally created for CarCover can be reused after removing their geometry LODs, which are redundant for this mod.

## Known Issues and Limitations

- **Initial installation:** A server wipe is required when installing the mod for the first time. Without it, existing saved vehicles may load with a camonet attached because of serialization changes.
- **Door slot configuration:** Door slots currently need to be defined manually for each supported vehicle.
- **Shape-changing attachments:** Multiple shape-changing slots are not currently supported.
- **Boat-specific behavior:** Some restrictions and movement-related options are not supported on boats.
