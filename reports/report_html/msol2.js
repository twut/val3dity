var report = {
  "CityObjects": {
    "id-1": {
      "errors": null,
      "primitives": [
        {
          "errors": null,
          "id": "id-1(0)",
          "numbersolids": 2,
          "primitives": [
            {
              "errors": null,
              "id": "none",
              "numberfaces": 6,
              "numbershells": 1,
              "numbervertices": 8,
              "type": "Solid",
              "validity": true
            },
            {
              "errors": [
                {
                  "code": 302,
                  "description": "SHELL_NOT_CLOSED",
                  "id": "",
                  "info": "Location hole: 1 0 3",
                  "type": "Error"
                }
              ],
              "id": "none",
              "numberfaces": 5,
              "numbershells": 1,
              "numbervertices": 8,
              "type": "Solid",
              "validity": false
            }
          ],
          "type": "MultiSolid",
          "validity": false
        }
      ],
      "type": "GenericCityObject",
      "validity": false
    }
  },
  "InputErrors": null,
  "Primitives": null,
  "input_file": "../data/cityjson/msol2.json",
  "invalid_cityobjects": 1,
  "invalid_primitives": 1,
  "overlap_tol": -1.0,
  "overview_errors": [
    302,
    404
  ],
  "overview_errors_no_primitives": [
    1,
    2
  ],
  "planarity_d2p_tol": 0.01,
  "planarity_n_tol": 20.0,
  "snap_tol": 0.001,
  "time": "Tue Oct 10 16:16:23 2017 CEST",
  "total_cityobjects": 1,
  "total_primitives": 1,
  "type": "val3dity report",
  "val3dity_version": "2.0 beta 1",
  "valid_cityobjects": 0,
  "valid_primitives": 0
}
