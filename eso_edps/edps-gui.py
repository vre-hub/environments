from pathlib import Path

import panel as pn

from edpsgui.gui.classifier import Classifier
from edpsgui.gui.dataset_creator import DatasetCreator
from edpsgui.gui.edps_ctl import EDPSControl
from edpsgui.gui.input_selector import InputSelector
from edpsgui.gui.job_viewer import JobViewer
from edpsgui.gui.reduction_history import ReductionHistory
from edpsgui.gui.reduction_queue import ReductionQueue
from edpsgui.gui.target_selector import TargetSelector
from edpsgui.gui.workflow import Workflow
from edpsgui.gui.workflow_selector import WorkflowSelector

pn.extension('tabulator', 'tree', 'ipywidgets', 'terminal', 'codeeditor', 'modal',
             css_files=["https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.2/css/all.min.css"],
             disconnect_notification='Connection lost, try reloading the page!',
             ready_notification='Application fully loaded.',
             notifications=True)

pn.state.notifications.position = 'top-center'

input_selector = InputSelector()
edps_ctl = EDPSControl()
workflow_selector = WorkflowSelector(edps_status=edps_ctl.param.edps_status)
workflow_graph = Workflow(edps_status=edps_ctl.param.edps_status,
                          workflow=workflow_selector.param.workflow)
target_selector = TargetSelector(edps_status=edps_ctl.param.edps_status,
                                 workflow=workflow_selector.param.workflow)
dataset_creator = DatasetCreator(edps_status=edps_ctl.param.edps_status,
                                 workflow=workflow_selector.param.workflow,
                                 inputs=input_selector.param.inputs,
                                 targets=target_selector.param.targets)
classifier = Classifier(edps_status=edps_ctl.param.edps_status,
                        workflow=workflow_selector.param.workflow,
                        inputs=input_selector.param.inputs)
reduction_queue = ReductionQueue(edps_status=edps_ctl.param.edps_status,
                                 workflow=workflow_selector.param.workflow)
reduction_history = ReductionHistory(edps_status=edps_ctl.param.edps_status,
                                     workflow=workflow_selector.param.workflow)

data_explorer = pn.Column(
    f'### 1. Select input data',
    input_selector,
    pn.layout.Divider(),
    f'### 2. Classify and inspect input data (optional)',
    classifier,
    pn.layout.Divider(),
    f'### 3. Select reduction target',
    target_selector,
    pn.layout.Divider(),
    f'### 4. Configure association (optional)',
    dataset_creator,
)

edps_aa_article = 'https://www.aanda.org/articles/aa/full_html/2024/01/aa47651-23/aa47651-23.html'
about_edps = pn.pane.HTML(f"""
If you make use of EDPS or its workflows for your research, we request to acknowledge
<a href="{edps_aa_article}" target="_blank">Freudling, Zampieri, Coccato et al 2024, A&A 681, A93.</a>
""")

reduction_tabs = pn.Tabs(
    ('Processing', reduction_queue),
    ('Processed', reduction_history),
    dynamic=True,
)


def update_tabs(event):
    if event == 2:
        reduction_queue.update_table()
    elif event == 3:
        reduction_history.update_table()


tabs = pn.Tabs(
    ('Workflow', workflow_graph),
    ('Raw Data', data_explorer),
    ('Processing Queue', reduction_queue),
    ('Processed Data', reduction_history),
    ('About EDPS', about_edps),
    dynamic=True,
)

pn.bind(update_tabs, tabs.param.active, watch=True)

layout = pn.Column(
    workflow_selector,
    pn.layout.Divider(),
    tabs,
    sizing_mode='scale_width'
)

logo_path = Path(__file__).resolve().parent / 'eso-logo.jpg'
template = pn.template.FastListTemplate(title='EDPS Dashboard', sidebar_width=250, logo=str(logo_path))
template.main.append(layout)
template.header.append(edps_ctl)

job_id = pn.state.location.query_params.get('job_id')
if job_id:
    JobViewer(job_id).servable()
else:
    template.servable()
