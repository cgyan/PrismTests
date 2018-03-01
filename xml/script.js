// load xml
// fill in summary table
// for each test suite
// -- add suite name to overview table
// -- add num of tests, failures, errors and time to overview table
// -- in test suites div write the test suite name
// -- create test suite table
// -- for each test case in suite
// -- -- add test case, status, details and time to row in test suite table
// -- add jump-to-top link

$(document).ready(function() {

    $.get('test_results.xml', function(data) {
        var summary = getDataForSummaryTable(data);
        populateSummaryTable(summary);

        $(data).find('testsuite').each(function() {
            var $test_suite = $(this);

            var test_suite_overview = getDataForOverviewTable($(this));
            addRowToOverviewTableWithTestSuiteOverview(test_suite_overview);

            $('#test_cases').append('<a name="' + test_suite_overview.name + '">');
            var table_id = test_suite_overview.name + '_test_suite_name';
            appendTestSuiteNameForTestSuiteTable(test_suite_overview.name);
            appendNewTestSuiteTable(table_id);

            $test_suite.find('testcase').each(function() {
                var $test_case = $(this);
                var test_case_summary = getDataForTestCase($(this));

                createRowForTestSuite(table_id, test_case_summary.name);
                addTestCaseNameToRow(test_case_summary.name);
                addStatusValueToRow(test_case_summary.name, test_case_summary.status);
                addTestCaseTimeToRow(test_case_summary.name, test_case_summary.time);

                $test_case.find('failure').each(function() {
                    updateRowWithErrorFormatting($(this), test_case_summary.name);
                });
            });
            appendJumpToTopLink();
        });
    });

    function getDataForSummaryTable(data) {
        var summary = {
            total_tests_ran: $(data).filter(':first').attr('tests'),
            total_failures: $(data).filter(':first').attr('failures'),
            total_errors: $(data).filter(':first').attr('errors'),
            total_disabled: $(data).filter(':first').attr('disabled'),
            total_time: $(data).filter(':first').attr('time'),
            percent_success: 0
        };
        var percent_success = (summary.total_tests_ran - summary.total_failures) / summary.total_tests_ran * 100;
        summary.percent_success = percent_success.toFixed(2);
        return summary;
    }

    function populateSummaryTable(summary) {
        var html = "<tr>" +
            "<td>" + summary.total_tests_ran + "</td>" +
            "<td>" + summary.total_failures + "</td>" +
            "<td>" + summary.total_errors + "</td>" +
            "<td>" + summary.total_disabled + "</td>" +
            "<td>" + summary.percent_success + "%</td>" +
            "<td>" + summary.total_time + "</td>" +
        "</tr>";
        $('#summary_table').append(html);
    }

    function addRowToOverviewTableWithTestSuiteOverview(testSuiteSummary) {
        $('#overview_table tr:last').after('<tr>' +
            '<td><a href="#' + testSuiteSummary.name +'">' + testSuiteSummary.name + '</a></td>' +
            '<td>' + testSuiteSummary.num_tests + '</td>' +
            '<td>' + testSuiteSummary.num_failures + '</td>' +
            '<td>' + testSuiteSummary.num_errors + '</td>' +
            '<td>' + testSuiteSummary.time + '</td>' +
        '</tr>');
    }

    function getDataForOverviewTable(testSuite) {
        var summary = {
            name: $(testSuite).attr('name'),
            num_tests: $(testSuite).attr('tests'),
            num_failures: $(testSuite).attr('failures'),
            num_errors: $(testSuite).attr('errors'),
            time: $(testSuite).attr('time')
        };
        return summary;
    }

    function appendTestSuiteNameForTestSuiteTable(name) {
        $('#test_cases').append('<h3> Test Suite: ' + name + '</h3>');
    }

    function appendNewTestSuiteTable(tableId) {
        var html = "<table id='" + tableId + "'>" +
            "<col class='even' width=45% />" +
            "<col class='even' width=5% />" +
            "<col class='even' width=45% />" +
            "<col class='even' width=5% />" +
            "<tr>" +
                "<th>Name</th>" +
                "<th>Status</th>" +
                "<th>Details</th>" +
                "<th>Time</th>" +
            "</tr>" +
        "</table>";
        $('#test_cases').append(html);
    }

    function createRowForTestSuite(tableId, testCaseName) {
        var html = "<tr id='" + testCaseName + "'>" +
            "<td class='td_test_case_name'></td>" +
            "<td class='td_pass_or_fail_status' style='background-color: #24ed4c;'></td>" +
            "<td class='td_details'></td>" +
            "<td class='td_time'></td>" +
        "</tr>";
        $('#' + tableId + ' tr:last').after(html);
    }

    function addTestCaseNameToRow(testCaseName) {
        var html = "";
        var array = testCaseName.match(/[A-Z][a-z]+/g);
        for (i = 0; i < array.length; ++i) {
            html += array[i] + ' ';
        }
        $('#' + testCaseName + ' .td_test_case_name').text(html);
    }

    function addStatusValueToRow(testCaseName, status) {
        $('#' + testCaseName + ' .td_pass_or_fail_status').text(status);
    }

    function addTestCaseTimeToRow(testCaseName, time) {
        $('#' + testCaseName + ' .td_time').text(time);
    }

    function getDataForTestCase(testCase) {
        var summary = {
            name: $(testCase).attr('name'),
            status: 'Passed',
            time: $(testCase).attr('time')
        };
        return summary;
    }

    function updateRowWithErrorFormatting(failure, testCaseName) {
        var message = $(failure).attr('message');
        $('#' + testCaseName + ' .td_test_case_name').css('color', 'red');
        $('#' + testCaseName + ' .td_details').text(message);
        $('#' + testCaseName + ' .td_details').css('color', 'red');
        $('#' + testCaseName + ' .td_pass_or_fail_status').text('Failed');
        $('#' + testCaseName + ' .td_pass_or_fail_status').css('background-color', '#ed2a24');
        $('#' + testCaseName + ' .td_pass_or_fail_status').css('color', '#ffffff');
    }

    function appendJumpToTopLink() {
        $('#test_cases').append('<p class="align_right"><a href="#jump_to_top">Jump to top</a></p>');
    }
});
